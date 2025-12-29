/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

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
 * \inmodule GenericFormatter
 * \inheaderfile GrantleeTheme/GenericFormatter
 *
 * \brief Convenience class for using a Grantlee theme.
 */
class GRANTLEETHEME_EXPORT GenericFormatter
{
public:
    /*!
     */
    GenericFormatter();
    /*!
     */
    explicit GenericFormatter(const QString &defaultHtmlMain, const QString &themePath);
    /*!
     */
    ~GenericFormatter();

    /*!
     */
    void setDefaultHtmlMainFile(const QString &name);
    /*!
     */
    void setTemplatePath(const QString &path);

    /*! Translation domain for the Grantlee localizer. */
    void setApplicationDomain(const QByteArray &domain);

    /*!
     */
    QString render(const QVariantHash &mapping) const;
    /*!
     */
    QString errorMessage() const;

    /*! Set template content from a string rather than a file. */
    void setTemplateContent(const QString &content);

    /*!
     */
    void reloadTemplate();

private:
    std::unique_ptr<GenericFormatterPrivate> const d;
};
}
