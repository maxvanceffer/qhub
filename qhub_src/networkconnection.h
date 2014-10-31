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

public slots:
    void finished();
    void error(const QNetworkReply::NetworkError &err);
    void notifyEncrypted();
private:
    class Private;
    Private * const d;
};
#endif // NETWORKCONNECTION_H
