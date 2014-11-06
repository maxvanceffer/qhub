#ifndef HUBSUBJECT_H
#define HUBSUBJECT_H

// Qt's includes
#include <QObject>
#include <QUrl>
#include <QString>

// Hub lin includes

/**
 * @brief The HubSubject class representd part of GitHub api response
 */
class HubSubject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QUrl latesCommentUrl READ latesCommentUrl WRITE setLatesCommentUrl NOTIFY latesCommentUrlChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
public:
    explicit HubSubject(QObject *parent = 0);
    ~HubSubject();

    /**
     * @brief type is type of object.
     * Can be either Issue, User and etc.
     *
     * @return QString
     */
    QString type() const;

    /**
     * @brief latesCommentUrl to ger last comment of this subject. Commit comment, or issue comment.
     * @return
     */
    QUrl latesCommentUrl() const;

    /**
     * @brief url of this subject
     * @return
     */
    QUrl url() const;

    /**
     * @brief title plain title of this subject
     * @return
     */
    QString title() const;

signals:
    void typeChanged(QString arg);
    void latesCommentUrlChanged(QUrl arg);
    void urlChanged(QUrl arg);
    void titleChanged(QString arg);

public slots:
    void setType(QString arg);
    void setLatesCommentUrl(QUrl arg);
    void setUrl(QUrl arg);
    void setTitle(QString arg);

private:
    class Private;
    Private * const d;
};

#endif // HUBSUBJECT_H

