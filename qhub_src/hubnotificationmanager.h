#ifndef HUBNOTIFICATIONMANAGER_H
#define HUBNOTIFICATIONMANAGER_H

// Qt's includes
#include <QObject>

// Hub lib's includes
#include "hubnotification.h"

/**
 * @brief The HubNotificationManager class used for polling GitHub for new notifications, in given interval
 *
 */
class HubNotificationManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(bool autoInterval READ autoInterval WRITE setAutoInterval NOTIFY autoIntervalChanged)
    Q_PROPERTY(QList<QObject*> notifications READ notifications NOTIFY notificationsChanged)
public:
    /**
     * Return instance of manager
     */
    static HubNotificationManager * instance();

    /**
     * Interval in milsec how often check for notifications. By default it set to 1 minutes.
     *
     * @brief interval
     * @return
     */
    int interval() const;

    /**
     * Count number of notifications
     *
     * @brief count
     * @return
     */
    int count() const;

    /**
     * @brief autoInterval
     * @return
     */
    bool autoInterval() const;

    /**
     * @brief notifications
     * @return
     */
    QList<QObject *> notifications() const;

signals:
    /**
     * @brief intervalChanged
     * @param arg
     */
    void intervalChanged(int arg);

    /**
     * @brief countChanged
     * @param arg
     */
    void countChanged(int arg);

    /**
     * @brief autoIntervalChanged
     * @param arg
     */
    void autoIntervalChanged(bool arg);

    /**
     * @brief notificationsChanged
     * @param arg
     */
    void notificationsChanged(QList<QObject*> arg);

public slots:
    /**
     * @brief setInterval
     * @param arg
     */
    void setInterval(int arg);

    /**
     * Force poll for update notifications
     *
     * @brief poll
     */
    void poll();

    /**
     * @brief setAutoInterval
     * @param arg
     */
    void setAutoInterval(bool arg);

    /**
     * @brief markAllAsRead mark all notifications as readed.
     * @note  All notifications will be removed, on success request.
     */
    void markAllAsRead();

    /**
     * @brief markAsRead mark exact notification as read
     */
    void markThreadAsRead( HubNotification * );

private slots:
    friend class JsonParser;

    /**
     * @brief startPolling
     */
    void startPolling();

    /**
     * @brief endPolling
     */
    void endPolling();

    /**
     * Proccess response from server
     *
     * @brief pollingResponse
     */
    void pollingResponse(QByteArray);

    /**
     * @brief updateNotifications
     */
    void updateNotifications(QList<HubNotification*>);

    /**
     * @brief rateLimitChanged
     */
    void rateLimitChanged(bool);

    /**
     * @brief syncPollTimeout
     */
    void syncPollTimeout(int);

    /**
     * @brief onMarkResponse
     */
    void onMarkResponse(QByteArray);

private:
    explicit HubNotificationManager(QObject *parent = 0);

    ~HubNotificationManager();

    class Private;
    Private * const d;
};



#endif // HUBNOTIFICATIONMANAGER_H

