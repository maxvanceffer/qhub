#include "hubauthority.h"
#include <QPointer>
#include <QDebug>

class HubAuthority::Private {
public:
    int m_id;
    int m_clientId;

    QString m_token;
    QString m_note;
    QString m_app;
    QString m_username;
    QString m_password;
    QStringList m_scope;

    QUrl m_noteUrl;
    QUrl m_appUrl;
    QUrl m_authorityUrl;

    QDateTime m_createdAt;
    QDateTime m_updatedAt;

    QPointer<HubUser> m_profile;
};

HubAuthority::HubAuthority(QObject *parent, const int &id):QObject(parent),d(new Private)
{
    d->m_profile = new HubUser(this);
    d->m_id = id;
    d->m_clientId = 0;
}

HubAuthority::~HubAuthority()
{
    delete d;
}

int HubAuthority::id() const
{
    return d->m_id;
}

QUrl HubAuthority::authorityUrl() const
{
    return d->m_authorityUrl;
}

void HubAuthority::setAuthorityUrl(QUrl arg)
{
    if (d->m_authorityUrl != arg) {
        d->m_authorityUrl = arg;
        emit authorityUrlChanged(arg);
    }
}

void HubAuthority::setApp(QString arg)
{
    if (d->m_app != arg) {
        d->m_app = arg;
        emit appChanged(arg);
    }
}

void HubAuthority::setAppUrl(QUrl arg)
{
    if (d->m_appUrl != arg) {
        d->m_appUrl = arg;
        emit appUrlChanged(arg);
    }
}

void HubAuthority::setClientId(int arg)
{
    if (d->m_clientId != arg) {
        d->m_clientId = arg;
        emit clientIdChanged(arg);
    }
}

void HubAuthority::setToken(QString arg)
{
    if (d->m_token != arg) {
        d->m_token = arg;
        emit tokenChanged(arg);
    }
}

void HubAuthority::setNote(QString arg)
{
    if (d->m_note != arg) {
        d->m_note = arg;
        emit noteChanged(arg);
    }
}

void HubAuthority::setNoteUrl(QUrl arg)
{
    if (d->m_noteUrl != arg) {
        d->m_noteUrl = arg;
        emit noteUrlChanged(arg);
    }
}

void HubAuthority::setCreatedAt(QDateTime arg)
{
    if (d->m_createdAt != arg) {
        d->m_createdAt = arg;
        emit createdAtChanged(arg);
    }
}

void HubAuthority::setUpdatedAt(QDateTime arg)
{
    if (d->m_updatedAt != arg) {
        d->m_updatedAt = arg;
        emit updatedAtChanged(arg);
    }
}

void HubAuthority::setScope(QStringList arg)
{
    if (d->m_scope != arg) {
        d->m_scope = arg;
        emit scopeChanged(arg);
    }
}

void HubAuthority::setUsername(QString arg)
{
    if (d->m_username != arg) {
        d->m_username = arg;
        emit usernameChanged(arg);
    }
}

void HubAuthority::setPassword(QString arg)
{
    if (d->m_password != arg) {
        d->m_password = arg;
        emit passwordChanged(arg);
    }
}

void HubAuthority::setId(int arg)
{
    if (d->m_id != arg) {
        d->m_id = arg;
        emit idChanged(arg);
    }
}

QString HubAuthority::app() const
{
    return d->m_app;
}

QUrl HubAuthority::appUrl() const
{
    return d->m_appUrl;
}

int HubAuthority::clientId() const
{
    return d->m_clientId;
}

QString HubAuthority::token() const
{
    return d->m_token;
}

QString HubAuthority::note() const
{
    return d->m_note;
}

QUrl HubAuthority::noteUrl() const
{
    return d->m_noteUrl;
}

QDateTime HubAuthority::createdAt() const
{
    return d->m_createdAt;
}

QDateTime HubAuthority::updatedAt() const
{
    return d->m_updatedAt;
}

QStringList HubAuthority::scope() const
{
    return d->m_scope;
}

bool HubAuthority::isAuthorized() const
{
    return !this->token().isEmpty();
}

bool HubAuthority::hasToken() const
{
    return !this->token().isEmpty();
}

QString HubAuthority::username() const
{
    return d->m_username;
}

QString HubAuthority::password() const
{
    return d->m_password;
}

HubUser *HubAuthority::profile() const
{
    qDebug()<<"Profile id "<<d->m_profile->id();
    return d->m_profile;
}
