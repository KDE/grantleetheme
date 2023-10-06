/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] bool operator==(const Theme &other) const;
    Theme &operator=(const Theme &other);

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] QString description() const;
    [[nodiscard]] QString themeFilename() const;
    [[nodiscard]] QString name() const;
    [[nodiscard]] QStringList displayExtraVariables() const;
    [[nodiscard]] QString dirName() const;
    [[nodiscard]] QString absolutePath() const;
    [[nodiscard]] QString author() const;
    [[nodiscard]] QString authorEmail() const;

    void addThemePath(const QString &path);

    [[nodiscard]] QString render(const QString &templateName, const QVariantHash &data, const QByteArray &applicationDomain = QByteArray());

    static void addPluginPath(const QString &path);

private:
    friend class ::GrantleeThemeTest;
    friend class ThemeManager;
    friend class ThemeManagerPrivate;
    Theme(const QString &themePath, const QString &dirName, const QString &defaultDesktopFileName);

    QSharedDataPointer<ThemePrivate> d;
};
}
