#include <QDebug>
#include <QPointer>
#include <QMutex>
#include <QHash>

#include "qhub.h"
#include "networkmanager.h"
#include "hubnotificationmanager.h"
#include "jsonparser.h"

static QHub * m_Instance = 0;

namespace QHubData {
  static const QString ConsumerKey = "c1607c81d339935f4c87";
  static const QString ConsumerSecretKey = "028ca80eb032461a9f6f8d8acef5bbaca2d85308";
  static const QString GitHubRoutesUrl = "https://api.github.com";
  static const QString GitHubAuth = QString("https://api.github.com/users/whatever?client_id=%1&client_secret=%2").arg(ConsumerKey,ConsumerSecretKey);

  static QHash<QString,QString> GitHubRouts;
}

class QHub::Private
{
public:
    QPointer<HubAuthority> m_current;
    QString m_error;
    int m_rateLimit;
};

QHub::QHub():d(new Private)
{
    d->m_current = new HubAuthority(this,-1);

    // Update routes
    NetworkManager::instance()->get(QHubData::GitHubRoutesUrl,this,"onRoutesReceived");
}

QHub::~QHub()
{
    HubNotification::debugObjectsCount();
    delete d;
}

QHub *QHub::instance()
{
    static QMutex mutex;
    if (!m_Instance)
    {
        mutex.lock();
        if (!m_Instance)
            m_Instance = new QHub;
        mutex.unlock();
    }

    return m_Instance;
}

QHash<QString, QString> QHub::routings() const
{
    return QHubData::GitHubRouts;
}

QString QHub::error() const
{
    return d->m_error;
}

HubAuthority *QHub::authority()
{
    return d->m_current;
}

void QHub::login(HubAuthority * user)
{
    if(d->m_current != user )
    {
        d->m_current->deleteLater();
    }

    d->m_current = user;

    QStringList scopes;
    scopes <<  "gist" << "user" << "public_repo" << "repo" << "repo_deployment" << "repo:status" << "notifications" ;

    QString json = JsonParser::buildAuthJson(scopes,"note","note url",QHubData::ConsumerKey,QHubData::ConsumerSecretKey);

    if(QHubData::GitHubRouts.value("authorizations_url").isEmpty()) {
        d->m_error = "No authorizations url is defined";
        qWarning()<<d->m_error;
        emit errorChanged(d->m_error);
        return;
    }

    qDebug()<<"Making request to "<<QHubData::GitHubRouts.value("authorizations_url");
    qDebug()<<"Builded json "<<json;

    NetworkManager::instance()->setAuthority(d->m_current);
    NetworkManager::instance()->post(QHubData::GitHubRouts.value("authorizations_url"),json.toLatin1(),this,"onLoginResponse");
}

void QHub::login(QString username, QString password)
{
    if(!d->m_current.isNull())
    {
        d->m_current->deleteLater();
    }

    d->m_current = new HubAuthority(this);
    d->m_current->setUsername(username);
    d->m_current->setPassword(password);

    login(d->m_current);
}

void QHub::setError(QString arg)
{
    if (d->m_error != arg) {
        d->m_error = arg;
        emit errorChanged(arg);
    }
}

void QHub::onRoutesReceived(QByteArray data)
{
    QHubData::GitHubRouts = JsonParser::parseRouts(data);
}

void QHub::onLoginResponse(QByteArray data)
{
    JsonResponse response = JsonParser::parseLoginResponse(data);
    if(!response.isError() && !d->m_current->token().isEmpty()) {
        qDebug()<<"Logged in, with token: "<<d->m_current->token();
    }

    if(d->m_current->token().isEmpty()) {
        qDebug()<<"Not logged in, error: "<<response.error();
        d->m_current->deleteLater();
        d->m_current = new HubAuthority(this);
        emit userFailedAuthorize();
        return;
    }

    emit authorityChanged(d->m_current);
    emit userAuthorized();

    QString url = QHubData::GitHubRouts.value("user_url");
    NetworkManager::instance()->get(url.replace("{user}",d->m_current->username()),this,"onUserResponse");
}

void QHub::onUserResponse(QByteArray data)
{
    JsonResponse response = JsonParser::parseProfileResponse(data);
    if(response.isError()) {
        qWarning()<<"Faile get profile data";
        return;
    }
    emit userProfileUpdated();
}
