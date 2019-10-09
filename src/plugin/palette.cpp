/*
 * Copyright (C) 2019 Volker Krause <vkrause@kde.org>
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
 */

#include "palette.h"

#include <grantlee/metatype.h>

#include <QPalette>

#define ROLE(R) { #R, QPalette::R }

static const struct {
    const char* name;
    QPalette::ColorRole role;
} color_roles[] = {
    ROLE(AlternateBase),
    ROLE(Base),
    ROLE(BrightText),
    ROLE(Button),
    ROLE(ButtonText),
    ROLE(Dark),
    ROLE(Highlight),
    ROLE(HighlightedText),
    ROLE(Light),
    ROLE(Link),
    ROLE(LinkVisited),
    ROLE(Mid),
    ROLE(Midlight),
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
    ROLE(PlaceholderText),
#endif    
    ROLE(Shadow),
    ROLE(Text),
    ROLE(ToolTipBase),
    ROLE(ToolTipText),
    ROLE(Window),
    ROLE(WindowText),
};

GRANTLEE_BEGIN_LOOKUP(QPalette)
    auto group = QPalette::Inactive;
    auto roleName = property;

    if (property.startsWith(QLatin1String("active"))) {
        roleName = property.mid(6);
        group = QPalette::Active;
    } else if (property.startsWith(QLatin1String("disabled"))) {
        roleName = property.mid(8);
        group = QPalette::Disabled;
    } else if (property.startsWith(QLatin1String("inactive"))) {
        roleName = property.mid(8);
        group = QPalette::Inactive;
    }

    for (const auto &role : color_roles) {
        if (roleName.compare(QLatin1String(role.name), Qt::CaseInsensitive) == 0) {
            return object.color(group, role.role);
        }
    }
    return {};
GRANTLEE_END_LOOKUP

void Palette::registerMetaType()
{
    Grantlee::registerMetaType<QPalette>();
}
