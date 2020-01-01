/*
  Copyright (c) 2016-2020 Laurent Montel <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "genericformatter.h"
#include "grantleethemeengine.h"
#include "grantleeki18nlocalizer.h"

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
    std::unique_ptr<Engine> mEngine;
    QString mErrorMessage;
    QSharedPointer<Grantlee::FileSystemTemplateLoader> mTemplateLoader;
    Grantlee::Template mTemplate;
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
        d->mTemplateLoader.reset(new Grantlee::FileSystemTemplateLoader);
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
    Grantlee::Context context(mapping);
    context.setLocalizer(d->mEngine->localizer());

    const QString contentHtml = d->mTemplate->render(&context);
    return contentHtml;
}

void GenericFormatter::setTemplateContent(const QString &content)
{
    d->mTemplate = d->mEngine->newTemplate(content, QStringLiteral("content"));
    if (d->mTemplate->error()) {
        d->mErrorMessage = d->mTemplate->errorString() + QLatin1String("<br>");
    }
}

void GenericFormatter::reloadTemplate()
{
    d->mTemplate = d->mEngine->loadByName(d->mDefaultMainFile);
    if (d->mTemplate->error()) {
        d->mErrorMessage += d->mTemplate->errorString() + QLatin1String("<br>");
    }
}
