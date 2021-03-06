#ifndef QHUB_H
#define QHUB_H

#include "qhub_global.h"
#include "hubauthority.h"

class QHUBSHARED_EXPORT QHub : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString error READ error WRITE setError NOTIFY errorChanged)
    Q_PROPERTY(HubAuthority * authority READ authority NOTIFY authorityChanged)
public:
    static QHub * instance();

    /**
     * Return predefined or updated routing, depend on network state
     *
     * @brief routings
     * @return
     */
    QHash<QString,QString> routings() const;

    /**
     * @brief error
     * @return
     */
    QString error() const;

    /**
     * @brief authority
     * @return
     */
    HubAuthority * authority();

signals:
    void userChanged(HubAuthority *);
    void userFailedAuthorize();
    void userAuthorized();
    void userUnauthorized();
    void userProfileUpdated();
    void userLoggedIn(HubAuthority *);
    void errorChanged(QString arg);
    void authorityChanged(HubAuthority * arg);

public slots:
    Q_INVOKABLE void login(HubAuthority *);

    Q_INVOKABLE void login( QString, QString );

    void setError(QString arg);

private slots:
    void onRoutesReceived(QByteArray);
    void onLoginResponse(QByteArray);
    void onUserResponse(QByteArray);

private :
    QHub();
    ~QHub();

    Q_DISABLE_COPY(QHub)

    class Private;
    Private * const d;
};

#endif // QHUB_H
