/*
  Copyright (c) 2016-2020 Laurent Montel <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef GRANTLEETHEME_GENERICFORMATTER_H
#define GRANTLEETHEME_GENERICFORMATTER_H

#include "grantleetheme_export.h"

#include <memory>

#include <QVariant>

class QString;

namespace GrantleeTheme {

class GenericFormatterPrivate;

/** Convenience class for using a Grantlee theme. */
class GRANTLEETHEME_EXPORT GenericFormatter
{
public:
    GenericFormatter();
    explicit GenericFormatter(const QString &defaultHtmlMain, const QString &themePath);
    ~GenericFormatter();

    void setDefaultHtmlMainFile(const QString &name);
    void setTemplatePath(const QString &path);

    /** Translation domain for the Grantlee localizer. */
    void setApplicationDomain(const QByteArray &domain);

    QString render(const QVariantHash &mapping) const;
    QString errorMessage() const;

    /** Set template content from a string rather than a file. */
    void setTemplateContent(const QString &content);

    void reloadTemplate();

private:
    std::unique_ptr<GenericFormatterPrivate> const d;
};

}

#endif // GRANTLEETHEME_GENERICFORMATTER_H
