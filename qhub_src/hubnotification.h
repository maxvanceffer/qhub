#ifndef HUBNOTIFICATION_H
#define HUBNOTIFICATION_H

#include <QObject>

class HubNotification : public QObject
{
    Q_OBJECT
public:
    explicit HubNotification(QObject *parent = 0);
    ~HubNotification();

signals:

public slots:
};



#endif // HUBNOTIFICATION_H

