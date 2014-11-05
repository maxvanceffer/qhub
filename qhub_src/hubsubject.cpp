#include "hubsubject.h"

class HubSubject::Private
{
public:
    QString m_type;
    QUrl m_latesCommentUrl;
    QUrl m_url;
    QString m_title;
};

HubSubject::HubSubject(QObject *parent) : QObject(parent),d(new Private)
{
}

HubSubject::~HubSubject()
{
    delete d;
}

QString HubSubject::type() const
{
    return d->m_type;
}

QUrl HubSubject::latesCommentUrl() const
{
    return d->m_latesCommentUrl;
}

QUrl HubSubject::url() const
{
    return d->m_url;
}

QString HubSubject::title() const
{
    return d->m_title;
}

void HubSubject::setType(QString arg)
{
    if (d->m_type == arg)
        return;

    d->m_type = arg;
    emit typeChanged(arg);
}

void HubSubject::setLatesCommentUrl(QUrl arg)
{
    if (d->m_latesCommentUrl == arg)
        return;

    d->m_latesCommentUrl = arg;
    emit latesCommentUrlChanged(arg);
}

void HubSubject::setUrl(QUrl arg)
{
    if (d->m_url == arg)
        return;

    d->m_url = arg;
    emit urlChanged(arg);
}

void HubSubject::setTitle(QString arg)
{
    if (d->m_title == arg)
        return;

    d->m_title = arg;
    emit titleChanged(arg);
}



