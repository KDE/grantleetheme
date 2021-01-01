/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef GRANTLEE_THEME_P_H
#define GRANTLEE_THEME_P_H

#include "grantleetheme.h"
#include "grantleeki18nlocalizer.h"

#include <grantlee/template.h>
#include <grantlee/templateloader.h>
#include <grantlee/engine.h>

namespace GrantleeTheme {
class GRANTLEETHEME_NO_EXPORT ThemePrivate : public QSharedData
{
public:
    ThemePrivate();
    ThemePrivate(const ThemePrivate &other);
    ~ThemePrivate();

    static void setupEngine();
    void setupLoader();
    Q_REQUIRED_RESULT Grantlee::Context createContext(const QVariantHash &data = QVariantHash(), const QByteArray &applicationDomain = QByteArray());
    Q_REQUIRED_RESULT QString errorTemplate(const QString &reason, const QString &templateName, const Grantlee::Template &errorTemplate);

    QStringList displayExtraVariables;
    QString themeFileName;
    QString description;
    QString name;
    QString dirName;
    QStringList absolutePaths;
    QString author;
    QString email;

    QSharedPointer<Grantlee::FileSystemTemplateLoader> loader;

    static QSharedPointer<GrantleeKi18nLocalizer> sLocalizer;
    static Grantlee::Engine *sEngine;
};
}

#endif
