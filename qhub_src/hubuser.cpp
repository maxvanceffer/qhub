#include "hubuser.h"

class HubUser::Private
{
public:
    int m_id;
    int m_gravatarId;
    int m_publicRepos;
    int m_publicGists;
    int m_followers;
    int m_following;
    bool m_siteAdmin;
    bool m_hireable;
    QUrl m_avatar;
    QUrl m_url;
    QUrl m_htmlUrl;
    QUrl m_blog;
    QString m_type;
    QString m_login;
    QString m_name;
    QString m_company;
    QString m_location;
    QString m_email;
    QDateTime m_createdAt;
    QDateTime m_updatedAt;
};

HubUser::HubUser(QObject *parent):QObject(parent),d(new Private)
{
    d->m_id = 0;
    d->m_gravatarId  = 0;
    d->m_publicGists = 0;
    d->m_publicRepos = 0;
}

int HubUser::id() const
{
    return d->m_id;
}

int HubUser::gravatarId() const
{
    return d->m_gravatarId;
}

int HubUser::publicRepos() const
{
    return d->m_publicRepos;
}

int HubUser::publicGists() const
{
    return d->m_publicGists;
}

int HubUser::followers() const
{
    return d->m_followers;
}

int HubUser::following() const
{
    return d->m_following;
}

bool HubUser::siteAdmin() const
{
    return d->m_siteAdmin;
}

bool HubUser::hireable() const
{
    return d->m_hireable;
}

QUrl HubUser::avatar() const
{
    return d->m_avatar;
}

QUrl HubUser::url() const
{
    return d->m_url;
}

QUrl HubUser::htmlUrl() const
{
    return d->m_htmlUrl;
}

QUrl HubUser::blog() const
{
    return d->m_blog;
}

QString HubUser::type() const
{
    return d->m_type;
}

QString HubUser::login() const
{
    return d->m_login;
}

QString HubUser::name() const
{
    return d->m_name;
}

QString HubUser::company() const
{
    return d->m_company;
}

QString HubUser::location() const
{
    return d->m_location;
}

QString HubUser::email() const
{
    return d->m_email;
}

QDateTime HubUser::createdAt() const
{
    return d->m_createdAt;
}

QDateTime HubUser::updatedAt() const
{
    return d->m_updatedAt;
}

void HubUser::setId(int arg)
{
    if (d->m_id != arg) {
        d->m_id = arg;
        emit idChanged(arg);
    }
}

void HubUser::setGravatarId(int arg)
{
    if (d->m_gravatarId != arg) {
        d->m_gravatarId = arg;
        emit gravatarIdChanged(arg);
    }
}

void HubUser::setPublicRepos(int arg)
{
    if (d->m_publicRepos != arg) {
        d->m_publicRepos = arg;
        emit publicReposChanged(arg);
    }
}

void HubUser::setPublicGists(int arg)
{
    if (d->m_publicGists != arg) {
        d->m_publicGists = arg;
        emit publicGistsChanged(arg);
    }
}

void HubUser::setFollowers(int arg)
{
    if (d->m_followers != arg) {
        d->m_followers = arg;
        emit followersChanged(arg);
    }
}

void HubUser::setFollowing(int arg)
{
    if (d->m_following != arg) {
        d->m_following = arg;
        emit followingChanged(arg);
    }
}

void HubUser::setSiteAdmin(bool arg)
{
    if (d->m_siteAdmin != arg) {
        d->m_siteAdmin = arg;
        emit siteAdminChanged(arg);
    }
}

void HubUser::setHireable(bool arg)
{
    if (d->m_hireable != arg) {
        d->m_hireable = arg;
        emit hireableChanged(arg);
    }
}

void HubUser::setAvatar(QUrl arg)
{
    if (d->m_avatar != arg) {
        d->m_avatar = arg;
        emit avatarChanged(arg);
    }
}

void HubUser::setUrl(QUrl arg)
{
    if (d->m_url != arg) {
        d->m_url = arg;
        emit urlChanged(arg);
    }
}

void HubUser::setHtmlUrl(QUrl arg)
{
    if (d->m_htmlUrl != arg) {
        d->m_htmlUrl = arg;
        emit htmlUrlChanged(arg);
    }
}

void HubUser::setBlog(QUrl arg)
{
    if (d->m_blog != arg) {
        d->m_blog = arg;
        emit blogChanged(arg);
    }
}

void HubUser::setType(QString arg)
{
    if (d->m_type != arg) {
        d->m_type = arg;
        emit typeChanged(arg);
    }
}

void HubUser::setLogin(QString arg)
{
    if (d->m_login != arg) {
        d->m_login = arg;
        emit loginChanged(arg);
    }
}

void HubUser::setName(QString arg)
{
    if (d->m_name != arg) {
        d->m_name = arg;
        emit nameChanged(arg);
    }
}

void HubUser::setCompany(QString arg)
{
    if (d->m_company != arg) {
        d->m_company = arg;
        emit companyChanged(arg);
    }
}

void HubUser::setLocation(QString arg)
{
    if (d->m_location != arg) {
        d->m_location = arg;
        emit locationChanged(arg);
    }
}

void HubUser::setEmail(QString arg)
{
    if (d->m_email != arg) {
        d->m_email = arg;
        emit emailChanged(arg);
    }
}

void HubUser::setCreatedAt(QDateTime arg)
{
    if (d->m_createdAt != arg) {
        d->m_createdAt = arg;
        emit createdAtChanged(arg);
    }
}

void HubUser::setUpdatedAt(QDateTime arg)
{
    if (d->m_updatedAt != arg) {
        d->m_updatedAt = arg;
        emit updatedAtChanged(arg);
    }
}
