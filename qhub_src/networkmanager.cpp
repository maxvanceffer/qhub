#include "networkconnection.h"
#include "networkmanager.h"

#include <QMutex>
#include <QPointer>

static NetworkManager * m_instance = 0;

class NetworkManager::Private
{
public:
    bool hasNetwork;
    QList<NetworkConnection*> connections;
    QPointer<HubAuthority> user;
};


NetworkManager::NetworkManager():d(new Private)
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager,SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),
            SLOT(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));
    connect(m_manager,SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),SLOT(authenticationRequired(QNetworkReply*,QAuthenticator*)));

    networkAccessibleChanged(m_manager->networkAccessible());
}

NetworkManager::~NetworkManager()
{
    delete m_manager;
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

void NetworkManager::get(const QUrl &url, QObject *object, const char *slot)
{
    QNetworkRequest request(url);
    QNetworkReply * rply = m_manager->get(request);

    NetworkConnection * connection = new NetworkConnection(rply,slot,object);

    connect(connection,SIGNAL(done()),connection,SLOT(deleteLater()));
    d->connections << connection;
}

void NetworkManager::post(const QUrl &url, QHttpMultiPart *data, QObject *object, const char *slot)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if(!d->user.isNull())
    {
        QByteArray credentials(QString("%1:%2").arg(d->user->username(),d->user->password()).toLatin1());
        request.setRawHeader("Authorization","Basic "+credentials.toBase64());
    }

    QNetworkReply * rply = m_manager->post(request,data);
    data->setParent(rply);

    NetworkConnection * connection = new NetworkConnection(rply,slot,object);

    connect(connection,SIGNAL(done()),connection,SLOT(deleteLater()));
    d->connections << connection;
}

void NetworkManager::post(const QUrl &url, QByteArray data, QObject *object, const char *slot )
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if(!d->user.isNull())
    {
        QByteArray credentials(QString("%1:%2").arg(d->user->username(),d->user->password()).toLatin1());
        request.setRawHeader("Authorization","Basic "+credentials.toBase64());
    }

    QNetworkReply * rply = m_manager->post(request,data);

    NetworkConnection * connection = new NetworkConnection(rply,slot,object);

    connect(connection,SIGNAL(done()),connection,SLOT(deleteLater()));
    d->connections << connection;
}

bool NetworkManager::hasNetwork() const
{
    return d->hasNetwork;
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
    qDebug()<<"Auth requaire ";
    if(d->user.isNull()) return;

    auth->setUser(d->user->username());
    auth->setPassword(d->user->password());
}
