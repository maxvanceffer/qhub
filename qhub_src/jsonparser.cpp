#include "jsonparser.h"
#include <QStringList>
#include <QVariantMap>

#include "qhub.h"

#ifdef Q_OS_LINUX
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#endif

#ifdef Q_OS_WIN
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#endif

#ifdef Q_OS_QNX
#include <bb/data/JsonDataAccess>
#endif

QMap<QString,QString> initProfileMap()
{
    QMap<QString,QString> map;
    // Fill profile map ["json key","qobject property"]
    map.insert("id","id");
    map.insert("avatar_url","avatar");
    map.insert("gravatar_id","gravatarId");
    map.insert("url","url");
    map.insert("html_url","htmlUrl");
    map.insert("type","type");
    map.insert("site_admin","siteAdmin");
    map.insert("name","name");
    map.insert("company","company");
    map.insert("blog","blog");
    map.insert("location","location");
    map.insert("login","login");
    map.insert("email","email");
    map.insert("hireable","hireable");
    map.insert("public_repos","publicRepos");
    map.insert("public_gists","publicGists");
    map.insert("followers","followers");
    map.insert("following","following");
    map.insert("created_at","createdAt");
    map.insert("updated_at","updatedAt");
    return map;
}

static QMap<QString,QString> profile = initProfileMap();

JsonParser::JsonParser()
{
}

QString JsonParser::buildAuthJson(QStringList scope, QString note, QString note_url, QString client_id, QString client_secret)
{
    QVariantMap map;
    map.insert("scope",scope);
    map.insert("note",note);
    map.insert("note_url",note_url);
    map.insert("client_id",client_id);
    map.insert("client_secret",client_secret);

    QJsonDocument doc;
    QJsonObject object;
    object.fromVariantMap(map);
    doc.setObject(object.fromVariantMap(map));

    return doc.toJson();
}

QHash<QString, QString> JsonParser::parseRouts(QByteArray json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json);

    QJsonObject obj = doc.object();
    QHash<QString,QString> hash;
    foreach( const QString &key, obj.keys())
    {
        hash.insert(key,obj.value(key).toString());
    }

    return hash;
}

JsonResponse JsonParser::parseLoginResponse(QByteArray json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json);

    QJsonObject obj = doc.object();
    QJsonObject app = obj.value("app").toObject();
    QJsonArray  scope = obj.value("scopes").toArray();
    HubAuthority * auth = QHub::instance()->authority();

    auth->setId(obj.value("id").toInt());
    auth->setAuthorityUrl(obj.value("url").toString());
    auth->setApp(app.value("name").toString());
    auth->setAppUrl(app.value("url").toString());
    auth->setClientId(app.value("client_id").toInt());
    auth->setToken(obj.value("token").toString());
    auth->setNote(obj.value("note").toString());
    auth->setNoteUrl(obj.value("note_url").toString());
    auth->setCreatedAt(QDateTime::fromString(obj.value("created_at").toString()));
    auth->setUpdatedAt(QDateTime::fromString(obj.value("updated_at").toString()));

    QStringList scp;
    for( int i = 0; i < scope.count(); i++ )
        scp << scope.at(i).toString();

    JsonResponse response;
    response.setError(false);
    response.setErrorMessage("");
    return response;
}

JsonResponse JsonParser::parseProfileResponse(QByteArray json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json);

    QJsonObject obj = doc.object();
    HubUser * auth = QHub::instance()->authority()->profile();

    foreach( const QString &json_key, profile.keys()) {
        QVariant value = obj.value(json_key).toVariant();
        auth->setProperty(profile.value(json_key).toLatin1(),value);
    }

    JsonResponse response;
    response.setError(false);
    response.setErrorMessage("");
    return response;
}

class JsonResponse::Private {
public:
    bool m_error;
    QString m_message;
};

JsonResponse::JsonResponse():d(new Private)
{
}

bool JsonResponse::isError() const
{
    return d->m_error;
}

QString JsonResponse::error() const
{
    return d->m_message;
}

void JsonResponse::setError(const bool &error)
{
    d->m_error = error;
}

void JsonResponse::setErrorMessage(const QString &message)
{
    d->m_message = message;
}
