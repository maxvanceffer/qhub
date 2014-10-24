#ifndef HUBMANAGER_H
#define HUBMANAGER_H

#include <QObject>

#include "qhub.h"

class HubManager : public QObject
{
    Q_OBJECT
public:
    explicit HubManager(QObject *parent = 0);

signals:

public slots:
    void authorityChanged(HubAuthority *);
    void userChanged();
};

#endif // HUBMANAGER_H
