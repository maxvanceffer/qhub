#ifndef HUBGIST_H
#define HUBGIST_H

// Qt's include
#include <QObject>
#include <QUrl>

// Hub lib includes
#include "hubuser.h"

class HubGist : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
//    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
//    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
//    Q_PROPERTY(bool isPublic READ isPublic WRITE setIsPublic NOTIFY isPublicChanged)
//    Q_PROPERTY(HubUser * owner READ owner WRITE setOwner NOTIFY ownerChanged)
public:
    explicit HubGist(QObject *parent = 0);
    ~HubGist();

signals:

public slots:
};



#endif // HUBGIST_H

