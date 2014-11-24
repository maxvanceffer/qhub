#ifndef HUBNOTIFICATION_H
#define HUBNOTIFICATION_H

// Qt's includes
#include <QObject>
#include <QDateTime>
#include <QUrl>

// Hub library includes
#include "hubsubject.h"
#include "hubrepository.h"

class HubNotification : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(bool isRead READ isRead WRITE setIsRead NOTIFY IsReadChanged)
    Q_PROPERTY(QString reason READ reason WRITE setReason NOTIFY reasonChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)
    Q_PROPERTY(QDateTime readedAt READ readedAt WRITE setReadedAt NOTIFY readedAtChanged)
    Q_PROPERTY(HubSubject * subject READ subject WRITE setSubject NOTIFY subjectChanged)
    Q_PROPERTY(HubRepository * repository READ repository WRITE setRepository NOTIFY repositoryChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QUrl subscriptionUrl READ subscriptionUrl WRITE setSubscriptionUrl NOTIFY subscriptionUrlChanged)
    Q_PROPERTY(QString repositoryName READ repositoryName NOTIFY repositoryNameChanged)
public:
    explicit HubNotification(QObject *parent = 0);
    ~HubNotification();

    /**
     * @brief id of this notification on GitHub
     * @def 0
     * @return int
     */
    int id() const;

    /**
     * @brief IsRead return status of this notification Read or Unread
     * @def false
     * @return bool
     */
    bool isRead() const;

    /**
     * @brief reason why you recive this notification, subscribed, author and etc
     * @return QString
     */
    QString reason() const;

    /**
     * @brief updatedAt
     * @return
     */
    QDateTime updatedAt() const;

    /**
     * @brief readedAt
     * @return
     */
    QDateTime readedAt() const;

    /**
     * @brief subject
     * @return
     */
    HubSubject * subject() const;

    /**
     * @brief type
     * @return
     */
    QString type() const;

    /**
     * @brief url
     * @return
     */
    QUrl url() const;

    /**
     * @brief subscriptionUrl
     * @return
     */
    QUrl subscriptionUrl() const;

    /**
     * @brief repository of this notification
     * @return HubRepository
     */
    HubRepository * repository() const;

    static int debugObjectsCount();

    /**
     * @brief repositoryName
     * @return
     */
    QString repositoryName() const;

signals:
    void idChanged(int arg);
    void IsReadChanged(bool arg);
    void reasonChanged(QString arg);
    void updatedAtChanged(QDateTime arg);
    void readedAtChanged(QDateTime arg);
    void subjectChanged(HubSubject * arg);
    void typeChanged(QString arg);
    void urlChanged(QUrl arg);
    void subscriptionUrlChanged(QUrl arg);
    void repositoryChanged(HubRepository * arg);
    void repositoryNameChanged(QString arg);

public slots:
    void setId(int arg);
    void setIsRead(bool arg);
    void setReason(QString arg);
    void setUpdatedAt(QDateTime arg);
    void setReadedAt(QDateTime arg);
    void setSubject(HubSubject * arg);
    void setType(QString arg);
    void setUrl(QUrl arg);
    void setSubscriptionUrl(QUrl arg);
    void setRepository(HubRepository * arg);

private:
    class Private;
    Private * const d;
};

#endif // HUBNOTIFICATION_H

