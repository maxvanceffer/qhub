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
public:
    NetworkConnection( QNetworkReply *, const char * slot, QObject * );
    ~NetworkConnection();

signals:
    void done();

public slots:
    void finished();
    void error(const QNetworkReply::NetworkError &err);
    void notifyEncrypted();
private:
    class Private;
    Private * const d;
};
#endif // NETWORKCONNECTION_H
