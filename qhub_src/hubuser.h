#ifndef HUBUSER_H
#define HUBUSER_H

#include "qhub_global.h"

#include <QObject>
#include <QUrl>
#include <QDateTime>

/**
 * @brief The HubUser class represents Hub user profile data. Such as login name, avatars, company name and etc.
 * @note All properties a semy read, it means after set first time them, you can not change them.
 */
class QHUBSHARED_EXPORT HubUser : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(int gravatarId READ gravatarId WRITE setGravatarId NOTIFY gravatarIdChanged)
    Q_PROPERTY(int publicRepos READ publicRepos WRITE setPublicRepos NOTIFY publicReposChanged)
    Q_PROPERTY(int publicGists READ publicGists WRITE setPublicGists NOTIFY publicGistsChanged)
    Q_PROPERTY(int followers READ followers WRITE setFollowers NOTIFY followersChanged)
    Q_PROPERTY(int following READ following WRITE setFollowing NOTIFY followingChanged)
    Q_PROPERTY(bool siteAdmin READ siteAdmin WRITE setSiteAdmin NOTIFY siteAdminChanged)
    Q_PROPERTY(bool hireable READ hireable WRITE setHireable NOTIFY hireableChanged)
    Q_PROPERTY(QUrl avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QUrl htmlUrl READ htmlUrl WRITE setHtmlUrl NOTIFY htmlUrlChanged)
    Q_PROPERTY(QUrl blog READ blog WRITE setBlog NOTIFY blogChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString company READ company WRITE setCompany NOTIFY companyChanged)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)
public:
    explicit HubUser(QObject *parent = 0);

    int id() const;

    int gravatarId() const;

    int publicRepos() const;

    int publicGists() const;

    int followers() const;

    int following() const;

    bool siteAdmin() const;

    bool hireable() const;

    QUrl avatar() const;

    QUrl url() const;

    QUrl htmlUrl() const;

    QUrl blog() const;

    QString type() const;

    QString login() const;

    QString name() const;

    QString company() const;

    QString location() const;

    QString email() const;

    QDateTime createdAt() const;

    QDateTime updatedAt() const;

signals:

    void idChanged(int arg);

    void gravatarIdChanged(int arg);

    void publicReposChanged(int arg);

    void publicGistsChanged(int arg);

    void followersChanged(int arg);

    void followingChanged(int arg);

    void siteAdminChanged(bool arg);

    void hireableChanged(bool arg);

    void avatarChanged(QUrl arg);

    void urlChanged(QUrl arg);

    void htmlUrlChanged(QUrl arg);

    void blogChanged(QUrl arg);

    void typeChanged(QString arg);

    void loginChanged(QString arg);

    void nameChanged(QString arg);

    void companyChanged(QString arg);

    void locationChanged(QString arg);

    void emailChanged(QString arg);

    void createdAtChanged(QDateTime arg);

    void updatedAtChanged(QDateTime arg);

public slots:

    void setId(int arg);
    void setGravatarId(int arg);
    void setPublicRepos(int arg);
    void setPublicGists(int arg);
    void setFollowers(int arg);
    void setFollowing(int arg);
    void setSiteAdmin(bool arg);
    void setHireable(bool arg);
    void setAvatar(QUrl arg);
    void setUrl(QUrl arg);
    void setHtmlUrl(QUrl arg);
    void setBlog(QUrl arg);
    void setType(QString arg);
    void setLogin(QString arg);
    void setName(QString arg);
    void setCompany(QString arg);
    void setLocation(QString arg);
    void setEmail(QString arg);
    void setCreatedAt(QDateTime arg);
    void setUpdatedAt(QDateTime arg);

private:
    class Private;
    Private * const d;
};

#endif // HUBUSER_H
