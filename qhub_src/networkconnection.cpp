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
    Private(const char * slot ):m_id(generateId()),m_slot(slot){}

    int m_id;

    QPointer<QNetworkReply> rply;
    QPointer<QObject> m_object;

    const char * m_slot;
    int m_rateLimitReset, m_rateMaxLimit, m_rateLimit, m_pollInterval;
};


NetworkConnection::NetworkConnection(QNetworkReply *rply, const char *slot, QObject * obj):d(new Private(slot))
{
    QPointer<QNetworkReply> ptr1 = rply;
    QPointer<QObject> ptr2 = obj;

    d->rply = ptr1;
    d->m_object = ptr2;
    d->m_rateLimit = 0;
    d->m_rateLimitReset = 0;
    d->m_rateMaxLimit   = 0;
    d->m_pollInterval   = 0;

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
    if(err) {
        qWarning()<<"Request error: "<<d->rply->errorString();
    }

    if(!QMetaObject::invokeMethod(d->m_object,d->m_slot,Q_ARG(QByteArray,"")))
    {
        qWarning()<<"Can not invoke method "<<d->m_slot<<" for finished request";
    }

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
    if(d->rply->hasRawHeader("X-RateLimit-Limit")) {
        int limit = d->rply->rawHeader("X-RateLimit-Limit").toInt();
        if(d->m_rateMaxLimit != limit && limit) {
            d->m_rateMaxLimit = limit;
            emit rateMaxLimitChanged(limit);
        }
    }

    if(d->rply->hasRawHeader("X-RateLimit-Remaining")) {
        int limit = d->rply->rawHeader("X-RateLimit-Remaining").toInt();
        if(d->m_rateLimit != limit && limit) {
            d->m_rateLimit = limit;
            emit rateLimitChanged(limit);
        }
    }

    if(d->rply->hasRawHeader("X-RateLimit-Reset")) {
        int limit = d->rply->rawHeader("X-RateLimit-Reset").toInt();
        if(d->m_rateLimitReset != limit && limit) {
            d->m_rateLimitReset = limit;
            emit rateLimitResetMilsec(limit);
        }
    }

    if(d->rply->hasRawHeader("X-Poll-Interval")) {
        int interval = d->rply->rawHeader("X-Poll-Interval").toInt();
        if(d->m_pollInterval != interval) {
            d->m_pollInterval = interval;
            emit pollTimeoutChanged(d->m_pollInterval);
        }
    }
}


int NetworkConnection::id() const
{
    return d->m_id;
}

int NetworkConnection::rateLimitReset() const
{
    return d->m_rateLimitReset;
}

int NetworkConnection::rateMaxLimit() const
{
    return d->m_rateMaxLimit;
}

int NetworkConnection::rateLimit() const
{
    return d->m_rateLimit;
}
