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
     * Create request using method get, and return network reply object
     *
     * @brief get
     * @param url
     * @return
     */
    void get(const QUrl &url, QObject * object, const char *slot );

    /**
     * @brief post
     * @param url
     * @param data
     * @param object
     * @param slot
     */
    void post(const QUrl &url, QHttpMultiPart * data, QObject * object, const char * slot);

    /**
     * @brief post
     * @param url
     * @param data
     * @param object
     * @param slot
     */
    void post(const QUrl &url, QByteArray data, QObject * object, const char * slot);

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
    void networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility);

    void authenticationRequired(QNetworkReply*,QAuthenticator*);

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
     * @brief m_manager
     */
    QNetworkAccessManager * m_manager;

    class Private;
    Private * const d;
};

#endif // NETWORKMANAGER_H
