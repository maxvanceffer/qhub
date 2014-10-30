#ifndef HUBREPO_H
#define HUBREPO_H

#include <QObject>

class HubRepo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    QString m_name;

public:
    explicit HubRepo(QObject *parent = 0);

QString name() const
{
    return m_name;
}

signals:

void nameChanged(QString arg);

public slots:

void setName(QString arg);
};

#endif // HUBREPO_H
