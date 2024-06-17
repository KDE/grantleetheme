/*
  SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "grantleetheme.h"
#include "grantleetheme_debug.h"
#include "grantleetheme_p.h"
#include "grantleethemeengine.h"
#include "qtresourcetemplateloader.h"
#include <config-grantleetheme.h>

#include <KConfig>
#include <KConfigGroup>
#include <KLocalizedString>

#include <QDir>
#include <QSharedPointer>

using namespace GrantleeTheme;

QSharedPointer<GrantleeKi18nLocalizer> GrantleeTheme::ThemePrivate::sLocalizer;
KTextTemplate::Engine *GrantleeTheme::ThemePrivate::sEngine = nullptr;

ThemePrivate::ThemePrivate()
    : QSharedData()
{
}

ThemePrivate::ThemePrivate(const ThemePrivate &other) = default;

ThemePrivate::~ThemePrivate() = default;

void ThemePrivate::setupEngine()
{
    sEngine = new GrantleeTheme::Engine();
}

void ThemePrivate::setupLoader()
{
    // Get the parent dir with themes, we set the theme directory separately

    QStringList templatePaths;
    for (const QString &absolutePath : std::as_const(absolutePaths)) {
        QDir dir(absolutePath);
        dir.cdUp();
        templatePaths << dir.absolutePath();
    }
    loader = QSharedPointer<GrantleeTheme::QtResourceTemplateLoader>::create();
    loader->setTemplateDirs(templatePaths);
    loader->setTheme(dirName);

    if (!sEngine) {
        ThemePrivate::setupEngine();
    }
    sEngine->addTemplateLoader(loader);
}
KTextTemplate::Context ThemePrivate::createContext(const QVariantHash &data, const QByteArray &applicationDomain)
{
    if (!sLocalizer) {
        sLocalizer.reset(new GrantleeKi18nLocalizer());
    }
    sLocalizer->setApplicationDomain(applicationDomain);
    KTextTemplate::Context ctx(data);
    ctx.setLocalizer(sLocalizer);
    return ctx;
}
QString ThemePrivate::errorTemplate(const QString &reason, const QString &origTemplateName, const KTextTemplate::Template &failedTemplate)
{
    KTextTemplate::Template tpl = sEngine->newTemplate(QStringLiteral("<h1>{{ error }}</h1>\n"
                                                                      "<b>%1:</b> {{ templateName }}<br>\n"
                                                                      "<b>%2:</b> {{ errorMessage }}")
                                                           .arg(i18n("Template"), i18n("Error message")),
                                                       QStringLiteral("TemplateError"));

    KTextTemplate::Context ctx = createContext();
    ctx.insert(QStringLiteral("error"), reason);
    ctx.insert(QStringLiteral("templateName"), origTemplateName);
    const QString errorString = failedTemplate ? failedTemplate->errorString() : i18n("(null template)");
    ctx.insert(QStringLiteral("errorMessage"), errorString);
    return tpl->render(&ctx);
}

Theme::Theme()
    : d(new ThemePrivate)
{
}

Theme::Theme(const QString &themePath, const QString &dirName, const QString &defaultDesktopFileName)
    : d(new ThemePrivate)
{
    const QString themeInfoFile = themePath + QLatin1Char('/') + defaultDesktopFileName;
    KConfig config(themeInfoFile);
    KConfigGroup group(&config, QStringLiteral("Desktop Entry"));
    if (group.isValid()) {
        d->dirName = dirName;
        d->absolutePaths.append(themePath);
        d->name = group.readEntry("Name", QString());
        d->description = group.readEntry("Description", QString());
        d->themeFileName = group.readEntry("FileName", QString());
        d->displayExtraVariables = group.readEntry("DisplayExtraVariables", QStringList());
    }
}

Theme::Theme(const Theme &other)

    = default;

Theme::~Theme() = default;

bool Theme::operator==(const Theme &other) const
{
    return isValid() && other.isValid() && d->absolutePaths == other.d->absolutePaths;
}

Theme &Theme::operator=(const Theme &other)
{
    if (this != &other) {
        d = other.d;
    }

    return *this;
}

bool Theme::isValid() const
{
    return !d->themeFileName.isEmpty() && !d->name.isEmpty();
}

QString Theme::description() const
{
    return d->description;
}

QString Theme::themeFilename() const
{
    return d->themeFileName;
}

QString Theme::name() const
{
    return d->name;
}

QStringList Theme::displayExtraVariables() const
{
    return d->displayExtraVariables;
}

QString Theme::dirName() const
{
    return d->dirName;
}

QString Theme::absolutePath() const
{
    if (!d->absolutePaths.isEmpty()) {
        return d->absolutePaths.at(0); // ####
    }
    return {};
}

QString Theme::author() const
{
    return d->author;
}

QString Theme::authorEmail() const
{
    return d->email;
}

void Theme::addThemePath(const QString &path)
{
    d->absolutePaths.append(path);
}

QString Theme::render(const QString &templateName, const QVariantHash &data, const QByteArray &applicationDomain)
{
    if (!d->loader) {
        d->setupLoader();
    }
    Q_ASSERT(d->loader);

    if (!d->loader->canLoadTemplate(templateName)) {
        qCWarning(GRANTLEETHEME_LOG) << "Cannot load template" << templateName
                                     << ", please check your installation. Tried in these dirs:" << d->loader->templateDirs();
        return {};
    }
    KTextTemplate::Template tpl = d->loader->loadByName(templateName, ThemePrivate::sEngine);
    if (!tpl || tpl->error()) {
        return d->errorTemplate(i18n("Template parsing error"), templateName, tpl);
    }
    KTextTemplate::Context ctx = d->createContext(data, applicationDomain);
    const QString result = tpl->render(&ctx);
    if (tpl->error()) {
        return d->errorTemplate(i18n("Template rendering error"), templateName, tpl);
    }

    return result;
}

void Theme::addPluginPath(const QString &path)
{
    if (!ThemePrivate::sEngine) {
        ThemePrivate::setupEngine();
    }

    QStringList paths = ThemePrivate::sEngine->pluginPaths();
    if (!paths.contains(path)) {
        paths.prepend(path);
        ThemePrivate::sEngine->setPluginPaths(paths);
    }
}
