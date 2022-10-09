/*
  SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once

#include "grantleeki18nlocalizer.h"
#include "grantleetheme.h"
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <grantlee/engine.h>
#include <grantlee/template.h>
#include <grantlee/templateloader.h>
#else
#include <KTextTemplate/engine.h>
#include <KTextTemplate/template.h>
#include <KTextTemplate/templateloader.h>
#endif

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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    Q_REQUIRED_RESULT Grantlee::Context createContext(const QVariantHash &data = QVariantHash(), const QByteArray &applicationDomain = QByteArray());
    Q_REQUIRED_RESULT QString errorTemplate(const QString &reason, const QString &templateName, const Grantlee::Template &errorTemplate);
#else
    Q_REQUIRED_RESULT KTextTemplate::Context createContext(const QVariantHash &data = QVariantHash(), const QByteArray &applicationDomain = QByteArray());
    Q_REQUIRED_RESULT QString errorTemplate(const QString &reason, const QString &templateName, const KTextTemplate::Template &errorTemplate);
#endif

    QStringList displayExtraVariables;
    QString themeFileName;
    QString description;
    QString name;
    QString dirName;
    QStringList absolutePaths;
    QString author;
    QString email;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QSharedPointer<Grantlee::FileSystemTemplateLoader> loader;
#else
    QSharedPointer<KTextTemplate::FileSystemTemplateLoader> loader;
#endif
    static QSharedPointer<GrantleeKi18nLocalizer> sLocalizer;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    static Grantlee::Engine *sEngine;
#else
    static KTextTemplate::Engine *sEngine;
#endif
};
}
