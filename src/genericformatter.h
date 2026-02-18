/*
  SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "grantleetheme_export.h"

#include <memory>

#include <QVariant>

class QString;

namespace GrantleeTheme
{
class GenericFormatterPrivate;
/*!
 * \class GrantleeTheme::GenericFormatter
 * \inmodule GrantleeTheme
 * \inheaderfile GrantleeTheme/GenericFormatter
 *
 * \brief Convenience class for using a Grantlee theme.
 */
class GRANTLEETHEME_EXPORT GenericFormatter
{
public:
    /*!
     * \brief Constructs a GenericFormatter object.
     */
    GenericFormatter();
    /*!
     * \brief Constructs a GenericFormatter object with specified HTML template and theme path.
     * \param defaultHtmlMain The default HTML main template filename
     * \param themePath The path to the theme directory
     */
    explicit GenericFormatter(const QString &defaultHtmlMain, const QString &themePath);
    /*!
     * \brief Destroys the GenericFormatter object.
     */
    ~GenericFormatter();

    /*!
     * \brief Sets the default HTML main template file.
     * \param name The filename of the HTML template
     */
    void setDefaultHtmlMainFile(const QString &name);
    /*!
     * \brief Sets the path to the template directory.
     * \param path The template directory path
     */
    void setTemplatePath(const QString &path);

    /*!
     * \brief Sets the translation domain for the Grantlee localizer.
     * \param domain The translation domain to use
     */
    void setApplicationDomain(const QByteArray &domain);

    /*!
     * \brief Renders the template with the given variable mappings.
     * \param mapping A hash of variable names and their values
     * \return The rendered template output as a QString
     */
    QString render(const QVariantHash &mapping) const;
    /*!
     * \brief Returns the last error message if rendering failed.
     * \return The error message, or an empty string if no error
     */
    QString errorMessage() const;

    /*!
     * \brief Sets the template content from a string rather than loading from a file.
     * \param content The template content as a string
     */
    void setTemplateContent(const QString &content);

    /*!
     * \brief Reloads the template from the file system.
     */
    void reloadTemplate();

private:
    std::unique_ptr<GenericFormatterPrivate> const d;
};
}
