#ifndef HUBISSUES_H
#define HUBISSUES_H

#include <QObject>

/**
 * Represents profile user issues
 *
 * @brief The HubIssues class
 */
class HubIssues : public QObject
{
    Q_OBJECT
public:
    explicit HubIssues(QObject *parent = 0);
    ~HubIssues();

signals:

public slots:
};



#endif // HUBISSUES_H

