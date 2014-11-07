#include "jsonparser.h"
#include <QStringList>
#include <QVariantMap>
#include <QDebug>

#include "qhub.h"
#include "hubnotificationmanager.h"
#include "hubnotification.h"

#include "qjson/parser.h"
#include "qjson/serializer.h"
#include "qjson/qobjecthelper.h"

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

void fillHubUser(HubUser * user, QVariantMap data)
{
    const QStringList dataKeys = data.keys();
    foreach( const QString &key, profile.keys()) {
        if(!dataKeys.contains(key)) continue;
        // Call set property mapped by key in json to property name of QObject
        user->setProperty(profile.value(key).toLatin1(),data.value(key));
    }
}

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

    QJson::Serializer serializer;
    bool ok = false;
    QByteArray json = serializer.serialize(map,&ok);
    if(!ok) {
        qWarning()<<"Can not create auth json";
    }

    return json;
}

QHash<QString, QString> JsonParser::parseRouts(QByteArray json)
{
    QJson::Parser parser;
    bool ok;

    QHash<QString,QString> hash;
    QVariantMap data = parser.parse(json,&ok).toMap();
    if(!ok) {
        qWarning()<<"Error parse routing json";
        return hash;
    }

    foreach( const QString &key, data.keys())
    {
        hash.insert(key,data.value(key).toString());
    }

    return hash;
}

JsonResponse JsonParser::parseLoginResponse(QByteArray json)
{
    JsonResponse response;
    QJson::Parser parser;
    bool ok;

    QVariantMap obj = parser.parse(json,&ok).toMap();
    if(!ok) {
        qWarning()<<"Error parse login response";
        response.setError(true);
        response.setErrorMessage("Error parse json");
        return response;
    }

    HubAuthority * auth = QHub::instance()->authority();
    QVariantMap app = obj.value("app").toMap();

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
    auth->setScope(obj.value("scope").toStringList());

    return response;
}

JsonResponse JsonParser::parseProfileResponse(QByteArray json)
{
    JsonResponse response;
    QJson::Parser parser;
    bool ok;

    QVariantMap obj = parser.parse(json,&ok).toMap();
    if(!ok) {
        response.setError(true);
        response.setErrorMessage("Error parse profile json response");
        return response;
    }

    HubUser * auth = QHub::instance()->authority()->profile();

    foreach( const QString &json_key, profile.keys()) {
        QVariant value = obj.value(json_key);
        auth->setProperty(profile.value(json_key).toLatin1(),value);
    }

    return response;
}

JsonResponse JsonParser::parseNotifications(QByteArray json)
{
    JsonResponse response;
    QJson::Parser parser;
    bool ok;

    QVariantList list = parser.parse(json,&ok).toList();
    if(!ok) {
        response.setError(true);
        response.setErrorMessage("Error parse notification json response");
        return response;
    }

    QList<HubNotification*> notifications;
    for( int i = 0; i < list.count(); i++ )
    {
        QVariantMap map = list.at(i).toMap();
        HubNotification * note  = new HubNotification(HubNotificationManager::instance());
        HubSubject      * subj  = new HubSubject(note);
        HubRepository   * repo  = new HubRepository(note);
        HubUser         * owner = new HubUser(repo);

        note->setId(map.value("id").toInt());
        note->setIsRead(!map.value("unread").toBool());
        note->setReason(map.value("reason").toString());
        note->setUpdatedAt(map.value("updated_at").toDateTime());
        note->setReadedAt(map.value("last_read_at").toDateTime());
        note->setSubscriptionUrl(map.value("subscription_url").toUrl());
        note->setUrl(map.value("url").toUrl());

        QVariantMap subjMap = map.value("subject").toMap();
        subj->setTitle(subjMap.value("title").toString());
        subj->setUrl(subjMap.value("url").toString());
        subj->setLatesCommentUrl(subjMap.value("latest_comment_url").toUrl());
        subj->setType(subjMap.value("type").toString());

        QVariantMap repoMap = map.value("repository").toMap();
        repo->setId(repoMap.value("id").toInt());
        repo->setName(repoMap.value("name").toString());
        repo->setFullName(repoMap.value("full_name").toString());
        repo->setDescription(repoMap.value("description").toString());
        repo->setIsFork(repoMap.value("fork").toBool());
        repo->setIsPrivate(repoMap.value("private").toBool());
        repo->setHtmlUrl(repoMap.value("html_url").toUrl());
        repo->setUrl(repoMap.value("url").toUrl());

        QVariantMap ownerMap = repoMap.value("owner").toMap();
        fillHubUser(owner,ownerMap);

        repo->setOwner(owner);
        note->setRepository(repo);
        note->setSubject(subj);
        notifications << note;
    }

    HubNotificationManager::instance()->updateNotifications(notifications);

    return response;
}

QByteArray JsonParser::objectToJson(QObject * obj, QStringList ignoreProperties)
{
    ignoreProperties << "objectName";
    QVariantMap mapped = QJson::QObjectHelper::qobject2qvariant(obj,ignoreProperties);
    QJson::Serializer serializer;
    return serializer.serialize(mapped);
}

class JsonResponse::Private {
public:
    bool m_error;
    QString m_message;
};

JsonResponse::JsonResponse():d(new Private)
{
    d->m_message = "";
    d->m_error   = false;
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
