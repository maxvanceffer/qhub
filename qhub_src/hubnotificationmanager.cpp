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
    QTimer m_pollingTimer;
    QDateTime m_lastRequestTime;
    QString lastModifiedFormat;
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

void HubNotificationManager::startPolling()
{
    const bool active = d->m_pollingTimer.isActive();
    if(active) return;

    // Poll for first time, and run poling timer
    poll();

    d->m_pollingTimer.start();
}

void HubNotificationManager::endPolling()
{

}

void HubNotificationManager::pollingResponse(QByteArray data)
{
    qDebug()<<"Notifications response: "<<data;

    d->m_requestId = 0;
}

HubNotificationManager::HubNotificationManager(QObject *parent) : QObject(parent), d(new Private)
{
    d->m_count    = 0;
    d->m_autoInterval = true;
    d->m_requestId = 0;
    d->m_pollingTimer.setInterval(60000);

    // Last-Modified: Tue, 15 Nov 1994 12:45:26 GMT

    connect(QHub::instance(),SIGNAL(userAuthorized()),SLOT(startPolling()));
    connect(QHub::instance(),SIGNAL(userUnauthorized()),SLOT(endPolling()));

    connect(&d->m_pollingTimer,SIGNAL(timeout()),SLOT(poll()));

    if(QHub::instance()->authority()->isAuthorized())
    {
        qDebug()<<"User already authorized start polling, now";
        startPolling();
    }
}

HubNotificationManager::~HubNotificationManager()
{

}



