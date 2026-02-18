/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

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
     * \brief Constructs a ThemeManager for the specified theme type.
     * \param themeType The type of theme to manage
     * \param defaultDesktopFileName The default desktop filename for the theme
     * \param actionCollection Optional KActionCollection for managing theme actions
     * \param path Optional custom path to theme directories
     * \param configFileName Optional custom configuration file name
     * \param parent Optional parent QObject
     */
    explicit ThemeManager(const QString &themeType,
                          const QString &defaultDesktopFileName,
                          KActionCollection *actionCollection = nullptr,
                          const QString &path = QString(),
                          const QString &configFileName = QString(),
                          QObject *parent = nullptr);
    /*!
     * \brief Destroys the ThemeManager.
     */
    ~ThemeManager() override;

    /*!
     * \brief Returns a map of all available themes.
     * \return A QMap mapping theme names to Theme objects
     */
    [[nodiscard]] QMap<QString, GrantleeTheme::Theme> themes() const;

    /*!
     * \brief Sets the action group for theme selection actions.
     * \param actionGroup The action group to use
     */
    void setActionGroup(QActionGroup *actionGroup);

    /*!
     * \brief Returns the action for the current theme selection.
     * \return A KToggleAction for selecting themes
     */
    [[nodiscard]] KToggleAction *actionForTheme();

    /*!
     * \brief Sets the menu for theme selection actions.
     * \param menu The action menu to use for theme selection
     */
    void setThemeMenu(KActionMenu *menu);

    /*!
     * \brief Displays extra variables for the specified theme.
     * \param themename The name of the theme
     * \return A list of extra variable names for the theme
     */
    [[nodiscard]] QStringList displayExtraVariables(const QString &themename) const;

    /*!
     * \brief Returns the theme object with the specified name.
     * \param themeName The name of the theme
     * \return The Theme object
     */
    [[nodiscard]] GrantleeTheme::Theme theme(const QString &themeName);

    /*!
     * \brief Returns the name of the currently configured theme.
     * \return The configured theme name
     */
    [[nodiscard]] QString configuredThemeName() const;
    /*!
     * \brief Returns the name of the currently configured theme for the specified type.
     * \param themeType The theme type
     * \return The configured theme name for the given type
     */
    [[nodiscard]] static QString configuredThemeName(const QString &themeType);

    /*!
     * \brief Finds the path to a theme resource.
     * \param path The base path to search
     * \param themeName The name of the theme
     * \param defaultDesktopFilename The default desktop filename to look for
     * \return The full path to the theme resource
     */
    [[nodiscard]] static QString pathFromThemes(const QString &path, const QString &themeName, const QString &defaultDesktopFilename);
    /*!
     * \brief Loads a theme from the specified path.
     * \param themePath The path to the theme directory
     * \param dirName The directory name within the theme
     * \param defaultDesktopFilename The default desktop filename to load
     * \return The loaded Theme object
     */
    [[nodiscard]] static GrantleeTheme::Theme loadTheme(const QString &themePath, const QString &dirName, const QString &defaultDesktopFilename);

Q_SIGNALS:
    /*!
     * \brief Emitted when the list of available themes has changed.
     */
    void themesChanged();
    /*!
     * \brief Emitted when a theme is selected by the user.
     */
    void grantleeThemeSelected();
    /*!
     * \brief Emitted when themes should be updated.
     */
    void updateThemes();

private:
    friend class ThemeManagerPrivate;
    std::unique_ptr<ThemeManagerPrivate> const d;
    Q_PRIVATE_SLOT(d, void directoryChanged())
};
}
