#ifndef TAGGING_H
#define TAGGING_H

#include <QObject>
#include <sys/user.h>
#include "tagdb.h"

class Tagging : public TAGDB
{
    Q_OBJECT
public:
    static Tagging *getInstance(const QString &app, const QString &version, const QString &uri, const QString &comment = QString());

    Q_INVOKABLE QVariantList get(const QString &query);

    Q_INVOKABLE bool tagExists(const QString &tag, const bool &strict = false);

    Q_INVOKABLE bool tag(const QString &tag, const QString &color=QString(), const QString &comment=QString());
    Q_INVOKABLE bool tagUrl(const QString &url, const QString &tag, const QString &color=QString(), const QString &comment=QString());
    Q_INVOKABLE bool tagAbstract(const QString &tag, const QString &key, const QString &lot, const QString &color = QString(), const QString &comment=QString());

    Q_INVOKABLE QVariantList getUrlsTags(const bool &strict = true);
    Q_INVOKABLE QVariantList getAbstractsTags(const bool &strict = true);
    Q_INVOKABLE QVariantList getAllTags(const bool &strict = true);
    Q_INVOKABLE QVariantList getUrls(const QString &tag, const bool &strict = true);
    Q_INVOKABLE QVariantList getUrlTags(const QString &url, const bool &strict = true);
    Q_INVOKABLE QVariantList getAbstractTags(const QString &key, const QString &lot, const bool &strict = true);

    /*STATIC METHODS*/

    static QString mac();
    static QString device();
    static QString id();

private:
    Tagging(const QString &app, const QString &version, const QString &uri, const QString &comment = QString(), QObject *parent = nullptr);
    ~Tagging();
    static Tagging* instance;
    void setApp(const QString &app, const QString &uri, const QString &version, const QString &comment = QString());

    QString application;
    QString version;
    QString comment;
    QString uri;

    bool app();
    bool user();

protected:
    bool abstract(const QString &key, const QString &lot, const QString &comment);

signals:

public slots:
};

#endif // TAGGING_H
