#include <QNetworkReply>
#include <QObject>

#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

/**
 * @brief The NetworkConnection class hold temporary network connection, and execute QObject slots on different events
 */
class NetworkConnection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id NOTIFY idChanged)
public:
    NetworkConnection( QNetworkReply *, const char * slot, QObject * );
    ~NetworkConnection();

    /**
     * Unique id of this request
     *
     * @brief id
     * @return
     */
    int id() const;

signals:
    void done();

    /**
     * When unique id changed
     *
     * @brief idChanged
     * @param arg
     */
    void idChanged(int arg);

    /**
     * This will fire if server response was not 200 or response code was above 400.
     * @note This function will fire before done()
     * @brief error
     * @param code
     * @param body
     */
    void error( int code, QByteArray body );

    /**
     *
     * @brief rateLimitChanged Will fire every request if rate limit changed in request. As for notifications api, if no changes was, then rate
     * limit will stay the same, so no signals will fire.
     */
    void rateLimitChanged(int);

    /**
     * @brief rateMaxLimitChanged Emited when maximum limit requests changed
     */
    void rateMaxLimitChanged(int);

    /**
     * @brief rateLimitResetMilsec
     */
    void rateLimitResetMilsec(int);

    /**
     * Will fire if changes in header keys will be detected
     *
     * @brief pollTimeoutChanged
     */
    void pollTimeoutChanged(int);

public slots:
    void finished();
    void error(const QNetworkReply::NetworkError &err);
    void notifyEncrypted();

private slots:
    void reportError();
    void parseRateLimit();

private:
    class Private;
    Private * const d;
};
#endif // NETWORKCONNECTION_H
