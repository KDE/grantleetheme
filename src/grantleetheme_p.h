/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once

#include "grantleetheme.h"
#include <KTextTemplate/Template>
#include <memory>

namespace KTextTemplate
{
class Context;
class Engine;
class FileSystemTemplateLoader;
}

namespace GrantleeTheme
{
class GrantleeKi18nLocalizer;
class GRANTLEETHEME_NO_EXPORT ThemePrivate : public QSharedData
{
public:
    ThemePrivate();
    ThemePrivate(const ThemePrivate &other);
    ~ThemePrivate();

    static void setupEngine();
    void setupLoader();
    [[nodiscard]] KTextTemplate::Context createContext(const QVariantHash &data = QVariantHash(), const QByteArray &applicationDomain = QByteArray());
    [[nodiscard]] QString errorTemplate(const QString &reason, const QString &templateName, const KTextTemplate::Template &errorTemplate);

    QStringList displayExtraVariables;
    QString themeFileName;
    QString description;
    QString name;
    QString dirName;
    QStringList absolutePaths;
    QString author;
    QString email;
    QSharedPointer<KTextTemplate::FileSystemTemplateLoader> loader;
    static QSharedPointer<GrantleeKi18nLocalizer> sLocalizer;
    static std::unique_ptr<KTextTemplate::Engine> sEngine;
};
}
