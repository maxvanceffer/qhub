#include "networkconnection.h"
#include "networkmanager.h"

#include <QMutex>
#include <QPointer>

static NetworkManager * m_instance = 0;

class NetworkManager::Private
{
public:
    bool hasNetwork;
    /**
     * @brief m_manager
     */
    QNetworkAccessManager * m_manager;

    QList<NetworkConnection*> connections;
    QPointer<HubAuthority> user;
    int rateMaxLimit, rateLimitLeft, rateResetTimeout;
};


NetworkManager::NetworkManager():d(new Private)
{
    d->rateLimitLeft = 0;
    d->rateMaxLimit  = 0;
    d->rateResetTimeout = 0;

    d->m_manager = new QNetworkAccessManager(this);
    connect(d->m_manager,SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),
            SLOT(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));
    connect(d->m_manager,SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),SLOT(authenticationRequired(QNetworkReply*,QAuthenticator*)));

    networkAccessibleChanged(d->m_manager->networkAccessible());
}

NetworkManager::~NetworkManager()
{
    delete d->m_manager;
}

NetworkManager *NetworkManager::instance()
{
    if(!m_instance) {
        QMutex mutex;
        mutex.lock();
        m_instance = new NetworkManager();
        mutex.unlock();
    }
    return m_instance;
}

int NetworkManager::get(const QUrl &url, QObject * object, const char *slot, const QNetworkRequest &request)
{
    if(isMaximumRateLimitExceeded()) {
        qWarning()<<"Maxim rate limit exceeded";
        return 0;
    }

    QNetworkRequest our_request = request;

    if(our_request.url().isEmpty())
        our_request.setUrl(url);

    QNetworkReply * rply = d->m_manager->get(our_request);

    NetworkConnection * connection = new NetworkConnection(rply,slot,object);

    makeDefaultConnections(connection);

    return connection->id();
}

int NetworkManager::post(const QUrl &url, QHttpMultiPart *data, QObject *object, const char *slot)
{
    if(isMaximumRateLimitExceeded()) {
        qWarning()<<"Maxim rate limit exceeded";
        return 0;
    }

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if(!d->user.isNull())
    {
        QByteArray credentials(QString("%1:%2").arg(d->user->username(),d->user->password()).toLatin1());
        request.setRawHeader("Authorization","Basic "+credentials.toBase64());
    }

    QNetworkReply * rply = d->m_manager->post(request,data);
    data->setParent(rply);

    NetworkConnection * connection = new NetworkConnection(rply,slot,object);

    makeDefaultConnections(connection);

    return connection->id();
}

int NetworkManager::post(const QUrl &url, QByteArray data, QObject *object, const char *slot )
{
    if(isMaximumRateLimitExceeded()) {
        qWarning()<<"Maxim rate limit exceeded";
        return 0;
    }

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if(!d->user.isNull())
    {
        QByteArray credentials(QString("%1:%2").arg(d->user->username(),d->user->password()).toLatin1());
        request.setRawHeader("Authorization","Basic "+credentials.toBase64());
    }

    QNetworkReply * rply = d->m_manager->post(request,data);

    NetworkConnection * connection = new NetworkConnection(rply,slot,object);

    makeDefaultConnections(connection);

    return connection->id();
}

bool NetworkManager::hasNetwork() const
{
    return d->hasNetwork;
}

QDateTime NetworkManager::rateLimitResetTimeout() const
{
    QDateTime dt;
    dt.setMSecsSinceEpoch(d->rateResetTimeout);
    return dt;
}

bool NetworkManager::isMaximumRateLimitExceeded() const
{
    return d->rateLimitLeft ? false : true;
}

void NetworkManager::setAuthority(HubAuthority * auth)
{
    d->user = auth;
}

void NetworkManager::networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility access)
{
    d->hasNetwork = (access > 0);
    emit networkAccessEnabled(d->hasNetwork);
}

void NetworkManager::authenticationRequired(QNetworkReply * rply, QAuthenticator * auth)
{
    Q_UNUSED(rply);
    if(d->user.isNull()) return;

    auth->setUser(d->user->username());
    auth->setPassword(d->user->password());
}

void NetworkManager::connectionDone()
{
    NetworkConnection * nc = qobject_cast<NetworkConnection*>(QObject::sender());

    if(!nc) return;

    int index = d->connections.indexOf(nc);
    if( index != -1 )
        d->connections.takeAt(index);

    nc->deleteLater();
}

void NetworkManager::makeDefaultConnections(NetworkConnection *connection)
{
    d->connections << connection;

    connect(connection,SIGNAL(rateLimitChanged(int)),SLOT(rateLimitChanged(int)));
    connect(connection,SIGNAL(rateMaxLimitChanged(int)),SLOT(rateMaxLimitChanged(int)));
    connect(connection,SIGNAL(rateLimitResetMilsec(int)),SLOT(rateTimoutLimitChanged(int)));

    connect(connection,SIGNAL(done()),connection,SLOT(deleteLater()));
    connect(connection,SIGNAL(done()),SLOT(connectionDone()));
}

void NetworkManager::rateLimitChanged(int value)
{
    qDebug()<<"Rate limit changed "<<value;
    // Check if we exceeded rate limit
    if(!value) {
        emit maximumRateLimitExceededChanged(true);
    }

    // Check if really changed
    if(d->rateLimitLeft != value) {
        d->rateLimitLeft = value;
        emit rateLimitChanged(value);
    }
}

void NetworkManager::rateMaxLimitChanged(int value)
{
    if(d->rateMaxLimit != value) {
        d->rateMaxLimit = value;
        emit rateMaxLimitChanged(value);
    }
}

void NetworkManager::rateTimoutLimitChanged(int value)
{
    if(d->rateResetTimeout != value) {
        d->rateResetTimeout = value;
        emit rateLimitResetTimeoutChanged(rateLimitResetTimeout());
    }
}
