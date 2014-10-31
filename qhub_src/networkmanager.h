#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QNetworkAccessManager>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QAuthenticator>

#include "hubauthority.h"

class NetworkManager : public QObject
{
    Q_OBJECT
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

signals:
    void networkAccessEnabled(bool);

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

    class Private;
    Private * const d;
};

#endif // NETWORKMANAGER_H
