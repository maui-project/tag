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

    Q_INVOKABLE void setApp(const QString &app, const QString &uri, const QString &version, const QString &comment = QString());
    Q_INVOKABLE bool tag(const QString &tag, const QString &color=QString(), const QString &comment=QString());
    Q_INVOKABLE bool tagUrl(const QString &url, const QString &tag, const QString &color=QString(), const QString &comment=QString());
    Q_INVOKABLE QStringList getTags(const QString &url);

    /*STATIC METHODS*/

    static QString mac();
    static QString device();
    static QString id();

private:
    Tagging(const QString &app, const QString &version, const QString &uri, const QString &comment = QString(), QObject *parent = nullptr);
    ~Tagging();
    static Tagging* instance;

    QString application;
    QString version;
    QString comment;
    QString uri;

    bool app();
    bool user();

signals:

public slots:
};

#endif // TAGGING_H
