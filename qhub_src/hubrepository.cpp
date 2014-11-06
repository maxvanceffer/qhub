#include "hubrepository.h"

#include <QPointer>

class HubRepository::Private
{
public:
    int m_id;
    bool m_isPrivate;
    bool m_isFork;
    QUrl m_url;
    QUrl m_htmlUrl;
    QString m_name;
    QString m_fullName;
    QString m_description;
    QPointer<HubUser> m_owner;
};

HubRepository::HubRepository(QObject *parent):QObject(parent),d(new Private)
{
    d->m_id = 0;
    d->m_isPrivate = false;
    d->m_isFork = false;
}

QString HubRepository::name() const
{
    return d->m_name;
}

int HubRepository::id() const
{
    return d->m_id;
}

bool HubRepository::isPrivate() const
{
    return d->m_isPrivate;
}

QUrl HubRepository::url() const
{
    return d->m_url;
}

bool HubRepository::isFork() const
{
    return d->m_isFork;
}

QUrl HubRepository::htmlUrl() const
{
    return d->m_htmlUrl;
}

QString HubRepository::description() const
{
    return d->m_description;
}

HubUser *HubRepository::owner() const
{
    return d->m_owner;
}

QString HubRepository::fullName() const
{
    return d->m_fullName;
}

void HubRepository::setName(QString arg)
{
    if (d->m_name != arg) {
        d->m_name = arg;
        emit nameChanged(arg);
    }
}

void HubRepository::setId(int arg)
{
    if (d->m_id == arg)
        return;

    d->m_id = arg;
    emit idChanged(arg);
}

void HubRepository::setIsPrivate(bool arg)
{
    if (d->m_isPrivate == arg)
        return;

    d->m_isPrivate = arg;
    emit isPrivateChanged(arg);
}

void HubRepository::setUrl(QUrl arg)
{
    if (d->m_url == arg)
        return;

    d->m_url = arg;
    emit urlChanged(arg);
}

void HubRepository::setIsFork(bool arg)
{
    if (d->m_isFork == arg)
        return;

    d->m_isFork = arg;
    emit isForkChanged(arg);
}

void HubRepository::setHtmlUrl(QUrl arg)
{
    if (d->m_htmlUrl == arg)
        return;

    d->m_htmlUrl = arg;
    emit htmlUrlChanged(arg);
}

void HubRepository::setDescription(QString arg)
{
    if (d->m_description == arg)
        return;

    d->m_description = arg;
    emit descriptionChanged(arg);
}

void HubRepository::setOwner(HubUser *arg)
{
    if (d->m_owner == arg)
        return;

    d->m_owner = arg;
    emit ownerChanged(arg);
}

void HubRepository::setFullName(QString arg)
{
    if (d->m_fullName == arg)
        return;

    d->m_fullName = arg;
    emit fullNameChanged(arg);
}
