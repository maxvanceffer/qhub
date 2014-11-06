#ifndef HUBREPO_H
#define HUBREPO_H

// Qt's includes
#include <QObject>
#include <QUrl>

// Hub lib's includes
#include "hubuser.h"

class HubRepository : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(bool isPrivate READ isPrivate WRITE setIsPrivate NOTIFY isPrivateChanged)
    Q_PROPERTY(bool isFork READ isFork WRITE setIsFork NOTIFY isForkChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QUrl htmlUrl READ htmlUrl WRITE setHtmlUrl NOTIFY htmlUrlChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString fullName READ fullName WRITE setFullName NOTIFY fullNameChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(HubUser * owner READ owner WRITE setOwner NOTIFY ownerChanged)
public:
    explicit HubRepository(QObject *parent = 0);

    /**
     * @brief name of this repository
     * @return QString
     */
    QString name() const;

    int id() const;

    /**
     * @brief isPrivate detect if this is private repo
     * @return
     */
    bool isPrivate() const;

    /**
     * @brief url of this repository ( not a html url )
     * Will return all data about this repo in json
     * @return
     */
    QUrl url() const;

    /**
     * @brief isFork detect if this repo is a fork of other
     * @return
     */
    bool isFork() const;

    /**
     * @brief htmlUrl return url to html version of project on GitHub
     * @return
     */
    QUrl htmlUrl() const;

    /**
     * @brief description return repo description text
     * @return QString
     */
    QString description() const;

    /**
     * @brief owner return link to the HubUser of owner of this repo
     * @return
     */
    HubUser * owner() const;

    /**
     * @brief fullName return sleshed name, like owner_name/repo_name
     * @return
     */
    QString fullName() const;

signals:
    void nameChanged(QString arg);
    void idChanged(int arg);
    void isPrivateChanged(bool arg);
    void urlChanged(QUrl arg);
    void isForkChanged(bool arg);
    void htmlUrlChanged(QUrl arg);
    void descriptionChanged(QString arg);
    void ownerChanged(HubUser * arg);
    void fullNameChanged(QString arg);

public slots:
    void setName(QString arg);
    void setId(int arg);
    void setIsPrivate(bool arg);
    void setUrl(QUrl arg);
    void setIsFork(bool arg);
    void setHtmlUrl(QUrl arg);
    void setDescription(QString arg);
    void setOwner(HubUser * arg);
    void setFullName(QString arg);

private:
   class Private;
   Private * const d;
};

#endif // HUBREPO_H
