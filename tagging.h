#ifndef TAGGING_H
#define TAGGING_H

#include <QObject>
#include "tagdb.h"

class Tagging : public TAGDB
{
    Q_OBJECT
public:
    explicit Tagging(QObject *parent = nullptr);
    explicit Tagging(const QString &app, const QString &version, const QString &comment = QString(), QObject *parent = nullptr);
    ~Tagging();
    Q_INVOKABLE void setApp(const QString &app, const QString &version, const QString &comment = QString());
    Q_INVOKABLE bool tag(const QString &tag, const QString &color=QString(), const QString &comment=QString());
    Q_INVOKABLE bool tagUrl(const QString &url, const QString &tag, const QString &color=QString(), const QString &comment=QString());
    Q_INVOKABLE QStringList getTags(const QString &url);

private:
    QString application;
    QString version;
    QString comment;

    bool app();


signals:

public slots:
};

#endif // TAGGING_H
