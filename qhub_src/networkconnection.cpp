#include "networkconnection.h"
#include <QPointer>

static int requestCount = 0;

int generateId()
{
    if(requestCount >= 1000000)
    {
        requestCount = 0;
    }

    return ++requestCount;
}

class NetworkConnection::Private
{
public:
    Private(const char * slot ):m_slot(slot),m_id(generateId()){}

    int m_id;

    QPointer<QNetworkReply> rply;
    QPointer<QObject> m_object;

    const char * m_slot;
};


NetworkConnection::NetworkConnection(QNetworkReply *rply, const char *slot, QObject * obj):d(new Private(slot))
{
    QPointer<QNetworkReply> ptr1 = rply;
    QPointer<QObject> ptr2 = obj;

    d->rply = ptr1;
    d->m_object = ptr2;

    connect(rply,SIGNAL(finished()),SLOT(finished()));
    connect(rply,SIGNAL(error(QNetworkReply::NetworkError)),SLOT(error(QNetworkReply::NetworkError)));
    connect(rply,SIGNAL(encrypted()),SLOT(notifyEncrypted()));
}

NetworkConnection::~NetworkConnection()
{
    d->rply->deleteLater();
    delete d;
}

void NetworkConnection::finished()
{
    if(d->rply.isNull()||d->m_object.isNull()) {
        emit done();
        qWarning()<<"QNetworkReply or QOBject was deleted before response is come, and slot invoked";
        return;
    }

    QByteArray data = d->rply->readAll();
    if(!QMetaObject::invokeMethod(d->m_object,d->m_slot,Q_ARG(QByteArray,data)))
    {
        qWarning()<<"Can not invoke method "<<d->m_slot<<" for finished request";
    }

    emit done();
}

void NetworkConnection::error(const QNetworkReply::NetworkError &err)
{
    emit done();
}

void NetworkConnection::notifyEncrypted()
{
    qDebug()<<"Request use encrypted protocol";
}


int NetworkConnection::id() const
{
    return d->m_id;
}
