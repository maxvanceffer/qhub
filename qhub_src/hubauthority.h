#ifndef HUBAUTHORITY_H
#define HUBAUTHORITY_H

#include "hubuser.h"

#include <QObject>
#include <QUrl>
#include <QStringList>
#include <QDateTime>

class QHUBSHARED_EXPORT HubAuthority : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QUrl authorityUrl READ authorityUrl WRITE setAuthorityUrl NOTIFY authorityUrlChanged)
    Q_PROPERTY(QString app READ app WRITE setApp NOTIFY appChanged)
    Q_PROPERTY(QUrl appUrl READ appUrl WRITE setAppUrl NOTIFY appUrlChanged)
    Q_PROPERTY(int clientId READ clientId WRITE setClientId NOTIFY clientIdChanged)
    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)
    Q_PROPERTY(QString note READ note WRITE setNote NOTIFY noteChanged)
    Q_PROPERTY(QUrl noteUrl READ noteUrl WRITE setNoteUrl NOTIFY noteUrlChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)
    Q_PROPERTY(QStringList scope READ scope WRITE setScope NOTIFY scopeChanged)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(HubUser * profile READ profile NOTIFY profileChanged)
public:
    explicit HubAuthority(QObject *parent = 0, const int &id = -1 );
    ~HubAuthority();

    int id() const;

    QUrl authorityUrl() const;

    QString app() const;

    QUrl appUrl() const;

    int clientId() const;

    QString token() const;

    QString note() const;

    QUrl noteUrl() const;

    QDateTime createdAt() const;

    QDateTime updatedAt() const;

    QStringList scope() const;

    bool isAuthorized() const;

    bool hasToken() const;

    QString username() const;

    QString password() const;

    HubUser * profile() const;

signals:

    void idChanged(int arg);

    void authorityUrlChanged(QUrl arg);

    void appChanged(QString arg);

    void appUrlChanged(QUrl arg);

    void clientIdChanged(int arg);

    void tokenChanged(QString arg);

    void noteChanged(QString arg);

    void noteUrlChanged(QUrl arg);

    void createdAtChanged(QDateTime arg);

    void updatedAtChanged(QDateTime arg);

    void scopeChanged(QStringList arg);

    void usernameChanged(QString arg);

    void passwordChanged(QString arg);

    void profileChanged(HubUser * arg);

public slots:
    /**
     * Authority url can be set only once. Once url is set, then you can't changed it
     *
     * @brief setAuthorityUrl
     * @param arg
     */
    void setAuthorityUrl(QUrl arg);

    /**
     * App name can be set only once. Once name is set, then you can't changed it
     *
     * @brief setApp
     * @param arg
     */
    void setApp(QString arg);

    /**
     * App url can be set only once. Once url is set, then you can't changed it
     *
     * @brief setAppUrl
     * @param arg
     */
    void setAppUrl(QUrl arg);

    /**
     * Client id can be set only once. Once url is set, then you can't changed it
     *
     * @brief setClientId
     * @param arg
     */
    void setClientId(int arg);

    /**
     * Token can be set only once. Once token is set, then you can't changed it
     * @brief setToken
     * @param arg
     */
    void setToken(QString arg);

    /**
     * Note can be set only once. Once note is set, then you can't changed it
     * @brief setNote
     * @param arg
     */
    void setNote(QString arg);

    /**
     * Note url can be set only once. Once url is set, then you can't changed it
     * @brief setNoteUrl
     * @param arg
     */
    void setNoteUrl(QUrl arg);

    /**
     * Created at url can be set only once. Once created at is set, then you can't changed it
     * @brief setCreatedAt
     * @param arg
     */
    void setCreatedAt(QDateTime arg);

    /**
     * @brief setUpdatedAt
     * @param arg
     */
    void setUpdatedAt(QDateTime arg);

    /**
     * @brief setScope
     * @param arg
     */
    void setScope(QStringList arg);

    /**
     * Once token is set, you can not changed user name
     * @brief setUsername
     * @param arg
     */
    void setUsername(QString arg);

    /**
     * Once token is set, you can not changed user name
     * @brief setPassword
     * @param arg
     */
    void setPassword(QString arg);

    void setId(int arg);

private:
    class Private;
    Private * const d;
};

#endif // HUBAUTHORITY_H
