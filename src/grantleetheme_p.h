/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once

#include "grantleeki18nlocalizer.h"
#include "grantleetheme.h"
#include <KTextTemplate/Engine>
#include <KTextTemplate/Template>
#include <KTextTemplate/TemplateLoader>

namespace GrantleeTheme
{
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
    static KTextTemplate::Engine *sEngine;
};
}
