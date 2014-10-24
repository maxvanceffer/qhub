#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QString>
#include <QHash>

class JsonResponse;
class JsonParser
{
public:
    JsonParser();

    static QString buildAuthJson(QStringList scope, QString note, QString note_url, QString client_id, QString client_secret);

    static QHash<QString,QString> parseRouts(QByteArray);

    static JsonResponse parseLoginResponse(QByteArray);

    static JsonResponse parseProfileResponse(QByteArray);
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