/*
  Copyright (c) 2013-2018 Montel Laurent <montel@kde.org>

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
#ifndef GRANTLEETHEME_H
#define GRANTLEETHEME_H

#include "grantleetheme_export.h"

#include <QString>
#include <QStringList>
#include <QVariantHash>
#include <QSharedDataPointer>

class GrantleeThemeTest;

namespace GrantleeTheme {
class ThemeManager;
class ThemePrivate;

class GRANTLEETHEME_EXPORT Theme
{
public:
    explicit Theme();
    Theme(const Theme &other);
    ~Theme();

    Q_REQUIRED_RESULT bool operator==(const Theme &other) const;
    Theme &operator=(const Theme &other);

    Q_REQUIRED_RESULT bool isValid() const;

    Q_REQUIRED_RESULT QString description() const;
    Q_REQUIRED_RESULT QString themeFilename() const;
    Q_REQUIRED_RESULT QString name() const;
    Q_REQUIRED_RESULT QStringList displayExtraVariables() const;
    Q_REQUIRED_RESULT QString dirName() const;
    Q_REQUIRED_RESULT QString absolutePath() const;
    Q_REQUIRED_RESULT QString author() const;
    Q_REQUIRED_RESULT QString authorEmail() const;

    Q_REQUIRED_RESULT QString render(const QString &templateName, const QVariantHash &data, const QByteArray &applicationDomain = QByteArray());

    static void addPluginPath(const QString &path);

private:
    friend class ::GrantleeThemeTest;
    friend class ThemeManager;
    Theme(const QString &themePath, const QString &dirName, const QString &defaultDesktopFileName);

    QSharedDataPointer<ThemePrivate> d;
};
}

#endif // GRANTLEETHEME_H
