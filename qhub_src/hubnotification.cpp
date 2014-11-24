#include "hubnotification.h"

#include <QPointer>
#include <QDebug>

static int countObj = 0;

class HubNotification::Private
{
public:
    int m_id;
    bool m_IsRead;
    QString m_reason;
    QDateTime m_updatedAt;
    QDateTime m_readedAt;
    QPointer<HubSubject> m_subject;
    QPointer<HubRepository> m_repository;
    QString m_type;
    QUrl m_url;
    QUrl m_subscriptionUrl;
};

HubNotification::HubNotification(QObject *parent) : QObject(parent),d(new Private)
{
    d->m_id = 0;
    d->m_IsRead = false;
    countObj++;
}

HubNotification::~HubNotification()
{
    countObj--;
    delete d;
}

int HubNotification::id() const
{
    return d->m_id;
}

bool HubNotification::isRead() const
{
    return d->m_IsRead;
}

QString HubNotification::reason() const
{
    return d->m_reason;
}

QDateTime HubNotification::updatedAt() const
{
    return d->m_updatedAt;
}

QDateTime HubNotification::readedAt() const
{
    return d->m_readedAt;
}

HubSubject *HubNotification::subject() const
{
    return d->m_subject;
}

QString HubNotification::type() const
{
    return d->m_type;
}

QUrl HubNotification::url() const
{
    return d->m_url;
}

QUrl HubNotification::subscriptionUrl() const
{
    return d->m_subscriptionUrl;
}

HubRepository *HubNotification::repository() const
{
    return d->m_repository;
}

int HubNotification::debugObjectsCount()
{
    return countObj;
}

QString HubNotification::repositoryName() const
{
    return d->m_repository->name();
}

void HubNotification::setId(int arg)
{
    if (d->m_id == arg)
        return;

    d->m_id = arg;
    emit idChanged(arg);
}

void HubNotification::setIsRead(bool arg)
{
    if (d->m_IsRead == arg)
        return;

    d->m_IsRead = arg;
    emit IsReadChanged(arg);
}

void HubNotification::setReason(QString arg)
{
    if (d->m_reason == arg)
        return;

    d->m_reason = arg;
    emit reasonChanged(arg);
}

void HubNotification::setUpdatedAt(QDateTime arg)
{
    if (d->m_updatedAt == arg)
        return;

    d->m_updatedAt = arg;
    emit updatedAtChanged(arg);
}

void HubNotification::setReadedAt(QDateTime arg)
{
    if (d->m_readedAt == arg)
        return;

    d->m_readedAt = arg;
    emit readedAtChanged(arg);
}

void HubNotification::setSubject(HubSubject *arg)
{
    if (d->m_subject == arg || !arg)
        return;

    d->m_subject = arg;
    d->m_subject->setParent(arg);
    emit subjectChanged(arg);
}

void HubNotification::setType(QString arg)
{
    if (d->m_type == arg)
        return;

    d->m_type = arg;
    emit typeChanged(arg);
}

void HubNotification::setUrl(QUrl arg)
{
    if (d->m_url == arg)
        return;

    d->m_url = arg;
    emit urlChanged(arg);
}

void HubNotification::setSubscriptionUrl(QUrl arg)
{
    if (d->m_subscriptionUrl == arg)
        return;

    d->m_subscriptionUrl = arg;
    emit subscriptionUrlChanged(arg);
}

void HubNotification::setRepository(HubRepository *arg)
{
    if (d->m_repository == arg || !arg)
        return;

    d->m_repository = arg;
    d->m_repository->setParent(this);
    emit repositoryNameChanged(arg->name());
    emit repositoryChanged(arg);
}



