#include "tagging.h"
#include <QMimeDatabase>

Tagging::Tagging(QObject *parent) : TAGDB(parent)
{}

Tagging::Tagging(const QString &app, const QString &version, const QString &comment, QObject *parent) : TAGDB(parent)
{
    this->setApp(app, version, comment);
}

Tagging::~Tagging()
{

}

void Tagging::setApp(const QString &app, const QString &version, const QString &comment)
{
    this->application = app;
    this->version = version;
    this->comment = comment;

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
        {TAG::KEYMAP[TAG::KEY::USER], UTIL::whoami()},
        {TAG::KEYMAP[TAG::KEY::DEVICE], QSysInfo::prettyProductName()}
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

bool Tagging::app()
{
//    QVariantMap app_map
//    {
//        {TAG::KEYMAP[TAG::KEY::TAG], tag},
//        {TAG::KEYMAP[TAG::KEY::ADD_DATE], QDateTime::currentDateTime()},
//        {TAG::KEYMAP[TAG::KEY::COMMENT], comment},
//        {TAG::KEYMAP[TAG::KEY::USER], UTIL::whoami()},
//        {TAG::KEYMAP[TAG::KEY::DEVICE], QSysInfo::prettyProductName()}
//    };

//    return this->insert(TAG::TABLEMAP[TAG::TABLE::APPS], app_map);
}


