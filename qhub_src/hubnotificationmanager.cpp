#include "hubnotificationmanager.h"
#include "qhub.h"
#include "networkmanager.h"
#include "networkconnection.h"
#include "jsonparser.h"

#include <QTimer>
#include <QDateTime>
#include <QMutex>

static HubNotificationManager * m_instance = 0;

class HubNotificationManager::Private
{
public:
    int m_count;
    int m_requestId;
    bool m_autoInterval;
    bool m_pollLastStatus;
    QTimer m_pollingTimer;
    QDateTime m_lastRequestTime;
    QString lastModifiedFormat;
    QList<HubNotification*> m_notifications;
};

HubNotificationManager *HubNotificationManager::instance()
{
    if(!m_instance) {
        QMutex mutex;
        mutex.lock();
        m_instance = new HubNotificationManager();
        mutex.unlock();
    }
    return m_instance;
}

int HubNotificationManager::interval() const
{
    return d->m_pollingTimer.interval();
}

int HubNotificationManager::count() const
{
    return d->m_count;
}

bool HubNotificationManager::autoInterval() const
{
    return d->m_autoInterval;
}

QList<QObject *> HubNotificationManager::notifications() const
{
    QList<QObject*> objects;
    foreach( HubNotification * n, d->m_notifications)
        objects << n;

    return objects;
}

void HubNotificationManager::setInterval(int arg)
{
    if (d->m_pollingTimer.interval() == arg)
        return;

    d->m_pollingTimer.setInterval(arg);
    emit intervalChanged(arg);
}

void HubNotificationManager::poll()
{
    // Check if we already requested notifications
    if(d->m_requestId) return;

    QString url = QHub::instance()->routings().value("notifications_url","");

    // TODO: Deside if we need stop polling timer also, on such error
    if(url.isEmpty() || !QHub::instance()->authority()->isAuthorized()) {
        qWarning()<<"No polling notifications, no url if defined";
        return;
    }

    if(!d->m_lastRequestTime.isValid())
        d->m_lastRequestTime = QDateTime::currentDateTime();

    QString modifiedSince = d->m_lastRequestTime.toUTC().toString("ddd, dd MMM yyyy hh:mm:ss") + "GMT";

    QNetworkRequest request(url);
    request.setRawHeader("Last-Modified",modifiedSince.toLatin1());

    d->m_requestId = NetworkManager::instance()->get(url,this,"pollingResponse");
}

void HubNotificationManager::setAutoInterval(bool arg)
{
    if (d->m_autoInterval == arg)
        return;

    d->m_autoInterval = arg;
    emit autoIntervalChanged(arg);
}

void HubNotificationManager::markAllAsRead()
{
    QUrl url = QHub::instance()->routings().value("notifications_url");
    NetworkManager::instance()->put(url,QByteArray(),this,"onMarkResponse");
}

void HubNotificationManager::markAsRead(HubNotification * note)
{
    QStringList ignPr = QStringList()<<"subject"<<"repository";
    QByteArray json = JsonParser::objectToJson(note,ignPr);
    qDebug()<<"Notification json: "<<json;

    QString prepareUrl = "https://api.github.com/repos/:owner/:repo/notifications";
    prepareUrl.replace(":owner",note->repository()->owner()->login());
    prepareUrl.replace(":repo",note->repository()->name());

    QUrl url = QUrl(prepareUrl);
    NetworkManager::instance()->put(url,json,this,"onMarkResponse");
}

void HubNotificationManager::startPolling()
{
    const bool active = d->m_pollingTimer.isActive();
    if(active) return;

    // Poll for first time, and run poling timer
    poll();

    d->m_pollLastStatus = true;
    d->m_pollingTimer.start();
}

void HubNotificationManager::endPolling()
{
    d->m_pollingTimer.stop();
    d->m_pollLastStatus = false;
}

void HubNotificationManager::pollingResponse(QByteArray data)
{
    d->m_requestId = 0;

//    qDebug()<<"Poll response "<<data;
    JsonResponse response = JsonParser::parseNotifications(data);
    if(response.isError()) {
        qWarning()<<"Error parse notifications: "<<response.error();
    }
}

HubNotificationManager::HubNotificationManager(QObject *parent) : QObject(parent), d(new Private)
{
    d->m_count    = 0;
    d->m_autoInterval = true;
    d->m_requestId = 0;
    d->m_pollLastStatus = false;
    d->m_pollingTimer.setInterval(60000);

    // Last-Modified: Tue, 15 Nov 1994 12:45:26 GMT

    connect(QHub::instance(),SIGNAL(userAuthorized()),SLOT(startPolling()));
    connect(QHub::instance(),SIGNAL(userUnauthorized()),SLOT(endPolling()));
    connect(&d->m_pollingTimer,SIGNAL(timeout()),SLOT(poll()));

    connect(NetworkManager::instance(),SIGNAL(maximumRateLimitExceededChanged(bool)),SLOT(rateLimitChanged(bool)));
    connect(NetworkManager::instance(),SIGNAL(pollTimeoutChanged(int)),SLOT(syncPollTimeout(int)));

    if(QHub::instance()->authority()->isAuthorized())
    {
        qDebug()<<"User already authorized start polling, now";
        startPolling();
    }
}

HubNotificationManager::~HubNotificationManager()
{
    delete d;
}

void HubNotificationManager::updateNotifications(QList<HubNotification *> list)
{
    // Remove other
    qDeleteAll(d->m_notifications.begin(),d->m_notifications.end());

    d->m_notifications.clear();
    d->m_notifications = list;
    d->m_count = 0;
    foreach( HubNotification * note, d->m_notifications )
        if(!note->isRead()) d->m_count++;

    emit countChanged(d->m_count);
    emit notificationsChanged(notifications());
}

void HubNotificationManager::rateLimitChanged(bool state)
{
    if(!state && d->m_pollingTimer.isActive())
    {
        d->m_pollingTimer.stop();
    }
    else if(state && !d->m_pollingTimer.isActive() && d->m_pollLastStatus)
    {
        d->m_pollingTimer.start();
    }
}

void HubNotificationManager::syncPollTimeout(int timeout)
{
    qDebug()<<"Say that sync timeout must be "<<timeout<<" sec";
    int milsec = timeout * 1000;
    if(d->m_autoInterval && milsec != d->m_pollingTimer.interval())
    {
        qDebug()<<"GitHub suggest "<<milsec<<" for updating notifications, apply new interval";
        d->m_pollingTimer.stop();
        d->m_pollingTimer.setInterval(milsec);
        d->m_pollingTimer.start();
    }
}

void HubNotificationManager::onMarkResponse(QByteArray json)
{
    qDebug()<<"Mark response "<<json;
}
