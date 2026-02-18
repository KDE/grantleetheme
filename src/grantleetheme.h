/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

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
/*!
 * \class GrantleeTheme::Theme
 * \inmodule GrantleeTheme
 * \inheaderfile GrantleeTheme/Theme
 *
 * \brief The Theme class.
 */
class ThemeManager;
class ThemeManagerPrivate;
class ThemePrivate;
class GRANTLEETHEME_EXPORT Theme
{
public:
    /*!
     * \brief Constructs an empty Theme object.
     */
    explicit Theme();
    /*!
     * \brief Copy constructor.
     * \param other The Theme to copy
     */
    Theme(const Theme &other);
    /*!
     * \brief Destroys the Theme object.
     */
    ~Theme();

    /*!
     * \brief Compares two Theme objects for equality.
     * \param other The Theme to compare with
     * \return true if themes are equal, false otherwise
     */
    [[nodiscard]] bool operator==(const Theme &other) const;
    /*!
     * \brief Assigns the given Theme to this object.
     * \param other The Theme to assign
     * \return A reference to this Theme object
     */
    Theme &operator=(const Theme &other);

    /*!
     * \brief Checks if this Theme object is valid.
     * \return true if the theme is valid, false otherwise
     */
    [[nodiscard]] bool isValid() const;

    /*!
     * \brief Returns the description of the theme.
     * \return The theme description
     */
    [[nodiscard]] QString description() const;
    /*!
     * \brief Returns the filename of the theme desktop file.
     * \return The theme filename
     */
    [[nodiscard]] QString themeFilename() const;
    /*!
     * \brief Returns the name of the theme.
     * \return The theme name
     */
    [[nodiscard]] QString name() const;
    /*!
     * \brief Returns a list of extra variables displayed by the theme.
     * \return A list of extra variable names
     */
    [[nodiscard]] QStringList displayExtraVariables() const;
    /*!
     * \brief Returns the directory name of the theme.
     * \return The directory name
     */
    [[nodiscard]] QString dirName() const;
    /*!
     * \brief Returns the absolute path to the theme directory.
     * \return The absolute path
     */
    [[nodiscard]] QString absolutePath() const;
    /*!
     * \brief Returns the author of the theme.
     * \return The author name
     */
    [[nodiscard]] QString author() const;
    /*!
     * \brief Returns the email address of the theme author.
     * \return The author's email address
     */
    [[nodiscard]] QString authorEmail() const;

    /*!
     * \brief Adds a path where theme files are located.
     * \param path The theme path to add
     */
    void addThemePath(const QString &path);

    /*!
     * \brief Renders the specified template with the given data.
     * \param templateName The name of the template to render
     * \param data A hash of variable names and their values
     * \param applicationDomain Optional translation domain for localization
     * \return The rendered template output
     */
    [[nodiscard]] QString render(const QString &templateName, const QVariantHash &data, const QByteArray &applicationDomain = QByteArray());

    /*!
     * \brief Adds a plugin path for theme plugins.
     * \param path The plugin path to add
     */
    static void addPluginPath(const QString &path);

private:
    friend class ::GrantleeThemeTest;
    friend class ThemeManager;
    friend class ThemeManagerPrivate;
    Theme(const QString &themePath, const QString &dirName, const QString &defaultDesktopFileName);

    QSharedDataPointer<ThemePrivate> d;
};
}
