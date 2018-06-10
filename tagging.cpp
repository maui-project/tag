#include "tagging.h"
#include <QMimeDatabase>
#include <QNetworkInterface>

Tagging::Tagging(const QString &app, const QString &version, const QString &uri, const QString &comment, QObject *parent) : TAGDB(parent)
{
    this->setApp(app, uri, version, comment);
}

Tagging::~Tagging() {}

Tagging* Tagging::instance = 0;
Tagging *Tagging::getInstance(const QString &app, const QString &version, const QString &uri, const QString &comment)
{
    if(!instance)
    {
        instance = new Tagging(app, version, uri, comment);
        qDebug() << "getInstance(): First instance\n";
        return instance;
    } else
    {
        qDebug()<< "getInstance(): previous instance\n";
        return instance;
    }
}

void Tagging::setApp(const QString &app, const QString &uri, const QString &version, const QString &comment)
{
    this->application = app;
    this->version = version;
    this->comment = comment;
    this->uri = uri;

    this->app();
}

bool Tagging::tag(const QString &tag, const QString &color, const QString &comment)
{
    QVariantMap tag_map
    {
        {TAG::KEYMAP[TAG::KEY::TAG], tag},
        {TAG::KEYMAP[TAG::KEY::COLOR], color},
        {TAG::KEYMAP[TAG::KEY::ADD_DATE], QDateTime::currentDateTime()},
        {TAG::KEYMAP[TAG::KEY::COMMENT], comment},
        {TAG::KEYMAP[TAG::KEY::DEVICE], this->device()}
    };

    return this->insert(TAG::TABLEMAP[TAG::TABLE::TAGS], tag_map);
}

bool Tagging::tagUrl(const QString &url, const QString &tag, const QString &color, const QString &comment)
{
    this->tag(tag, color, comment);

    QMimeDatabase mimedb;
    auto mime = mimedb.mimeTypeForFile(url);

    QVariantMap tag_url_map
    {
        {TAG::KEYMAP[TAG::KEY::URL], url},
        {TAG::KEYMAP[TAG::KEY::TAG], tag},
        {TAG::KEYMAP[TAG::KEY::TITLE], QFileInfo(url).baseName()},
        {TAG::KEYMAP[TAG::KEY::MIME], mime.name()},
        {TAG::KEYMAP[TAG::KEY::ADD_DATE], QDateTime::currentDateTime()},
        {TAG::KEYMAP[TAG::KEY::COMMENT], comment}
    };

    return this->insert(TAG::TABLEMAP[TAG::TABLE::TAGS_URLS], tag_url_map);
}

QStringList Tagging::getTags(const QString &url)
{
    return {};
}

QString Tagging::mac()
{
    QNetworkInterface mac;
    qDebug()<< "MAC ADDRES:"<< mac.hardwareAddress();
    return mac.hardwareAddress();
}

QString Tagging::device()
{
    return QSysInfo::prettyProductName();
}

QString Tagging::id()
{
#ifdef Q_OS_ANDROID
    return QSysInfo::machineHostName();
#else
    return QString(QSysInfo::machineUniqueId());
#endif
}

bool Tagging::app()
{
    qDebug()<<"REGISTER APP" << this->application<< this->uri<< this->version<< this->comment;
    QVariantMap app_map
    {
        {TAG::KEYMAP[TAG::KEY::APP], this->application},
        {TAG::KEYMAP[TAG::KEY::URI], this->uri},
        {TAG::KEYMAP[TAG::KEY::VERSION], this->version},
        {TAG::KEYMAP[TAG::KEY::ADD_DATE], QDateTime::currentDateTime()},
        {TAG::KEYMAP[TAG::KEY::COMMENT], this->comment},
    };

    this->insert(TAG::TABLEMAP[TAG::TABLE::APPS], app_map);

    this->user();

    QVariantMap users_apps_map
    {
        {TAG::KEYMAP[TAG::KEY::APP], this->application},
        {TAG::KEYMAP[TAG::KEY::URI], this->uri},
        {TAG::KEYMAP[TAG::KEY::MAC], this->id()},
        {TAG::KEYMAP[TAG::KEY::ADD_DATE], QDateTime::currentDateTime()},
    };

    this->insert(TAG::TABLEMAP[TAG::TABLE::APPS_USERS], users_apps_map);

}

bool Tagging::user()
{
    QVariantMap user_map
    {
        {TAG::KEYMAP[TAG::KEY::MAC], this->id()},
        {TAG::KEYMAP[TAG::KEY::NAME], UTIL::whoami()},
        {TAG::KEYMAP[TAG::KEY::LAST_SYNC], QDateTime::currentDateTime()},
        {TAG::KEYMAP[TAG::KEY::ADD_DATE], QDateTime::currentDateTime()},
        {TAG::KEYMAP[TAG::KEY::DEVICE], this->device()},
    };

    return this->insert(TAG::TABLEMAP[TAG::TABLE::USERS], user_map);
}


