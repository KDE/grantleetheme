/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/
#pragma once

#include "grantleetheme_export.h"

#include <QSharedDataPointer>
#include <QString>
#include <QStringList>
#include <QVariantHash>

class GrantleeThemeTest;

namespace GrantleeTheme
{
class ThemeManager;
class ThemeManagerPrivate;
class ThemePrivate;

/**
 * @brief The Theme class
 */
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

    void addThemePath(const QString &path);

    Q_REQUIRED_RESULT QString render(const QString &templateName, const QVariantHash &data, const QByteArray &applicationDomain = QByteArray());

    static void addPluginPath(const QString &path);

private:
    friend class ::GrantleeThemeTest;
    friend class ThemeManager;
    friend class ThemeManagerPrivate;
    Theme(const QString &themePath, const QString &dirName, const QString &defaultDesktopFileName);

    QSharedDataPointer<ThemePrivate> d;
};
}

