#ifndef APPINFO_H
#define APPINFO_H

#include <QString>
#include <QUrl>

class AppInfo
{
public:
    AppInfo();

    /**
     * Github application id
     *
     * @brief id
     * @return
     */
    QString id() const;

    /**
     * Application authorization id
     *
     * @brief idUrl
     * @return
     */
    QUrl idUrl() const;


};

#endif // APPINFO_H
