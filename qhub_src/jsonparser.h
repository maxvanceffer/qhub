#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QHash>

class JsonResponse;
class JsonParser : public QObject
{
    Q_OBJECT
public:
    JsonParser();

    static QString buildAuthJson(QStringList scope, QString note, QString note_url, QString client_id, QString client_secret);

    static QHash<QString,QString> parseRouts(QByteArray);

    static JsonResponse parseLoginResponse(QByteArray);

    static JsonResponse parseProfileResponse(QByteArray);

    static JsonResponse parseNotifications(QByteArray);

    static QByteArray objectToJson(QObject * , QStringList ignoreProperties = QStringList());
};

class JsonResponse {
public:
    JsonResponse();

    bool isError() const;

    QString error() const;

private:
    friend class JsonParser;

    void setError( const bool &);

    void setErrorMessage( const QString &);
private:
    class Private;
    Private  * const d;
};

#endif // JSONPARSER_H
