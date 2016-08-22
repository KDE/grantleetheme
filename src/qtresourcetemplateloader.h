/*
 * Copyright (C) 2016 Laurent Montel <montel@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef QTRESOURCETEMPLATELOADER_H
#define QTRESOURCETEMPLATELOADER_H
#include "grantlee/templateloader.h"
#include "grantleetheme_export.h"
namespace GrantleeTheme
{
class GRANTLEETHEME_EXPORT QtResourceTemplateLoader : public Grantlee::FileSystemTemplateLoader
{
public:
    QtResourceTemplateLoader(const QSharedPointer<Grantlee::AbstractLocalizer> localizer = QSharedPointer<Grantlee::AbstractLocalizer>());

    Grantlee::Template loadByName(const QString &fileName, const Grantlee::Engine *engine) const Q_DECL_OVERRIDE;
    bool canLoadTemplate(const QString &name) const Q_DECL_OVERRIDE;
};
}
#endif // QTRESOURCETEMPLATELOADER_H