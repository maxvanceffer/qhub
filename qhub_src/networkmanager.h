#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QNetworkAccessManager>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QAuthenticator>

#include "hubauthority.h"

class NetworkConnection;

/**
 * @brief The NetworkManager class manage all network connections to GitHub API. Also it manage max limits value, and other api params.
 *
 */
class NetworkManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDateTime rateLimitResetTimeout READ rateLimitResetTimeout NOTIFY rateLimitResetTimeoutChanged)
    Q_PROPERTY(bool isMaximumRateLimitExceeded READ isMaximumRateLimitExceeded NOTIFY maximumRateLimitExceededChanged)
    Q_PROPERTY(int pollTimeout READ pollTimeout NOTIFY pollTimeoutChanged)
public:
    static NetworkManager * instance();
    /**
     * Create request using method get, and return network reply object. If request has no url, then url param will be used for request.
     * If request param has url, then request url will be used, instead of url param.
     *
     * @brief get
     * @param url
     * @return int Id of request
     */
    int get(const QUrl &url, QObject * object, const char *slot, const QNetworkRequest &request = QNetworkRequest());

    /**
     * @brief post
     * @param url
     * @param data
     * @param object
     * @param slot
     * @return int Id of request
     */
    int post(const QUrl &url, QHttpMultiPart * data, QObject * object, const char * slot);

    /**
     * @brief post
     * @param url
     * @param data
     * @param object
     * @param slot
     * @return int Id of request
     */
    int post(const QUrl &url, QByteArray data, QObject * object, const char * slot);

    /**
     * @brief put make request with type put
     * @param url where to make request
     * @param data to put in content body
     * @param object to call slot on response
     * @param slot
     * @param request
     * @return
     */
    int put(const QUrl &url, const QByteArray &data, QObject * object, const char * slot, const QNetworkRequest &request = QNetworkRequest());

    /**
     * @brief hasNetwork
     * @return
     */
    bool hasNetwork() const;

    /**
     *
     * @brief authority
     * @return
     */
    HubAuthority * authority();

    /**
     * @brief rateLimitResetTimeout return time when rate limit will be dropped to max value of rate limit
     *
     * @return QDateTime
     */
    QDateTime rateLimitResetTimeout() const;

    bool isMaximumRateLimitExceeded() const;

    int pollTimeout() const;

signals:
    void networkAccessEnabled(bool);

    void rateLimitResetTimeoutChanged(QDateTime arg);

    void maximumRateLimitExceededChanged(bool arg);

    void pollTimeoutChanged(int arg);

public slots:
    void setAuthority(HubAuthority *);

private slots:
    /**
     * @brief networkAccessibleChanged
     */
    void networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility);

    /**
     * @brief authenticationRequired
     */
    void authenticationRequired(QNetworkReply*,QAuthenticator*);

    /**
     * @brief connectionDone
     */
    void connectionDone();

    /**
     * @brief makeDefaultConnections
     */
    void makeDefaultConnections(NetworkConnection*);

    void rateLimitChanged(int);

    void rateMaxLimitChanged(int);

    void rateTimoutLimitChanged(int);

    void setPollTimeout(int);

private:
    /**
     * @brief NetworkManager
     */
    NetworkManager();

    /**
     *
     */
    ~NetworkManager();

    /**
     * @brief operator =
     * @param other
     * @return
     */
    NetworkManager& operator = ( const NetworkManager &other );

    /**
     * PIMPL
     */
    class Private;
    Private * const d;
};

#endif // NETWORKMANAGER_H
