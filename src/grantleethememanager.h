/*
  SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once

#include "grantleetheme.h"
#include "grantleetheme_export.h"
#include <QMap>
#include <QObject>

#include <memory>

class QActionGroup;
class KActionCollection;
class KToggleAction;
class KActionMenu;

namespace GrantleeTheme
{
class ThemeManagerPrivate;

/*!
 * \class GrantleeTheme::ThemeManager
 * \inmodule GrantleeTheme
 * \inheaderfile GrantleeTheme/ThemeManager
 *
 * \brief The ThemeManager class.
 * \author Laurent montel <montel@kde.org>
 */
class GRANTLEETHEME_EXPORT ThemeManager : public QObject
{
    Q_OBJECT
public:
    /*!
     */
    explicit ThemeManager(const QString &themeType,
                          const QString &defaultDesktopFileName,
                          KActionCollection *actionCollection = nullptr,
                          const QString &path = QString(),
                          const QString &configFileName = QString(),
                          QObject *parent = nullptr);
    /*!
     */
    ~ThemeManager() override;

    /*!
     */
    [[nodiscard]] QMap<QString, GrantleeTheme::Theme> themes() const;

    /*!
     */
    void setActionGroup(QActionGroup *actionGroup);

    /*!
     */
    [[nodiscard]] KToggleAction *actionForTheme();

    /*!
     */
    void setThemeMenu(KActionMenu *menu);

    /*!
     */
    [[nodiscard]] QStringList displayExtraVariables(const QString &themename) const;

    /*!
     */
    [[nodiscard]] GrantleeTheme::Theme theme(const QString &themeName);

    /*!
     */
    [[nodiscard]] QString configuredThemeName() const;
    /*!
     */
    [[nodiscard]] static QString configuredThemeName(const QString &themeType);

    /*!
     */
    [[nodiscard]] static QString pathFromThemes(const QString &path, const QString &themeName, const QString &defaultDesktopFilename);
    /*!
     */
    [[nodiscard]] static GrantleeTheme::Theme loadTheme(const QString &themePath, const QString &dirName, const QString &defaultDesktopFilename);

Q_SIGNALS:
    /*!
     */
    void themesChanged();
    /*!
     */
    void grantleeThemeSelected();
    /*!
     */
    void updateThemes();

private:
    friend class ThemeManagerPrivate;
    std::unique_ptr<ThemeManagerPrivate> const d;
    Q_PRIVATE_SLOT(d, void directoryChanged())
};
}
