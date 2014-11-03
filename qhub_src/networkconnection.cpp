#include "networkconnection.h"
#include <QPointer>

static int requestCount = 0;
const static QList<QByteArray> xRateLimitHeaders = QList<QByteArray>() << "X-RateLimit-Limit"
                                                           << "X-RateLimit-Remaining"
                                                           << "X-RateLimit-Reset";

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

    if(d->rply->error() != QNetworkReply::NoError) return this->reportError();

    // Check if rate limit changed
    parseRateLimit();

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

void NetworkConnection::reportError()
{
    qWarning()<<"There was error proccess this request";
    qWarning()<<"Error: "<<d->rply->errorString();
}

void NetworkConnection::parseRateLimit()
{
    foreach( const QByteArray &header, d->rply->rawHeaderList())
    {
        qDebug()<<"Header: "<<header<<" Value: "<<d->rply->rawHeader(header);
    }

    if(d->rply->hasRawHeader("X-RateLimit-Limit")) {
        int limit = d->rply->rawHeader("X-RateLimit-Limit").toInt();

        if(limit) emit rateMaxLimitChanged(limit);
    }
    if(d->rply->hasRawHeader("X-RateLimit-Remaining")) {
        int limit = d->rply->rawHeader("X-RateLimit-Remaining").toInt();

        if(limit) emit rateLimitChanged(limit);
    }
    if(d->rply->hasRawHeader("X-RateLimit-Reset")) {
        int limit = d->rply->rawHeader("X-RateLimit-Reset").toInt();

        if(limit) emit rateLimitResetMilsec(limit);
    }
}


int NetworkConnection::id() const
{
    return d->m_id;
}
