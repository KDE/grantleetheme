/*
  Copyright (c) 2013-2020 Laurent Montel <montel@kde.org>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
