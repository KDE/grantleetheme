/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericformatter.h"
using namespace Qt::Literals::StringLiterals;

#include "grantleeki18nlocalizer.h"
#include "grantleethemeengine.h"

using namespace GrantleeTheme;

class GrantleeTheme::GenericFormatterPrivate
{
public:
    GenericFormatterPrivate()
        : mEngine(new Engine)
    {
    }

    QString mThemePath;
    QString mDefaultMainFile;
    std::unique_ptr<Engine> const mEngine;
    QString mErrorMessage;
    QSharedPointer<KTextTemplate::FileSystemTemplateLoader> mTemplateLoader;
    KTextTemplate::Template mTemplate;
};

GenericFormatter::GenericFormatter(const QString &defaultHtmlMain, const QString &themePath)
    : d(new GenericFormatterPrivate)
{
    d->mThemePath = themePath;
    d->mDefaultMainFile = defaultHtmlMain;
    setTemplatePath(d->mThemePath);
}

GenericFormatter::GenericFormatter()
    : d(new GenericFormatterPrivate)
{
}

GenericFormatter::~GenericFormatter() = default;

void GenericFormatter::setDefaultHtmlMainFile(const QString &name)
{
    if (d->mDefaultMainFile != name) {
        d->mDefaultMainFile = name;
        reloadTemplate();
    }
}

void GenericFormatter::setTemplatePath(const QString &path)
{
    if (!d->mTemplateLoader) {
        d->mTemplateLoader.reset(new KTextTemplate::FileSystemTemplateLoader);
    }
    d->mTemplateLoader->setTemplateDirs(QStringList() << path);
    d->mEngine->addTemplateLoader(d->mTemplateLoader);

    reloadTemplate();
}

void GenericFormatter::setApplicationDomain(const QByteArray &domain)
{
    d->mEngine->localizer()->setApplicationDomain(domain);
}

QString GenericFormatter::errorMessage() const
{
    return d->mErrorMessage;
}

QString GenericFormatter::render(const QVariantHash &mapping) const
{
    KTextTemplate::Context context(mapping);
    context.setLocalizer(d->mEngine->localizer());

    const QString contentHtml = d->mTemplate->render(&context);
    return contentHtml;
}

void GenericFormatter::setTemplateContent(const QString &content)
{
    d->mTemplate = d->mEngine->newTemplate(content, QStringLiteral("content"));
    if (d->mTemplate->error()) {
        d->mErrorMessage = d->mTemplate->errorString() + "<br>"_L1;
    }
}

void GenericFormatter::reloadTemplate()
{
    d->mTemplate = d->mEngine->loadByName(d->mDefaultMainFile);
    if (d->mTemplate->error()) {
        d->mErrorMessage += d->mTemplate->errorString() + "<br>"_L1;
    }
}
