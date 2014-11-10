#ifndef HUBGISTSMANAGER_H
#define HUBGISTSMANAGER_H

#include <QObject>

class HubGistsManager : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
public:
    static HubGistsManager * instance();

signals:

public slots:

private:
    explicit HubGistsManager(QObject *parent = 0);
    ~HubGistsManager();

    class Private;
    Private * const d;
};

#endif // HUBGISTSMANAGER_H

