/*
 * SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */

#pragma once
#include <KTextTemplate/TemplateLoader>
#include <QObject>

#include "grantleetheme_export.h"
namespace GrantleeTheme
{
/*!
 * \class GrantleeTheme::QtResourceTemplateLoader
 * \inmodule GrantleeTheme
 * \inheaderfile GrantleeTheme/QtResourceTemplateLoader
 *
 * \brief The QtResourceTemplateLoader class
 * \author Laurent montel <montel@kde.org>
 */
class GRANTLEETHEME_EXPORT QtResourceTemplateLoader : public KTextTemplate::FileSystemTemplateLoader
{
public:
    /*!
     * \brief Constructs a QtResourceTemplateLoader.
     * \param localizer Optional localizer instance for template localization
     */
    explicit QtResourceTemplateLoader(const QSharedPointer<KTextTemplate::AbstractLocalizer> localizer = QSharedPointer<KTextTemplate::AbstractLocalizer>());
    /*!
     * \brief Loads a template by name from Qt resources.
     * \param fileName The name of the template file to load
     * \param engine The Grantlee engine instance
     * \return The loaded template object
     */
    [[nodiscard]] KTextTemplate::Template loadByName(const QString &fileName, const KTextTemplate::Engine *engine) const override;

    /*!
     * \brief Checks whether a template can be loaded with the given name.
     * \param name The template name to check
     * \return true if the template can be loaded, false otherwise
     */
    [[nodiscard]] bool canLoadTemplate(const QString &name) const override;
};
}
