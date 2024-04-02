/*
 * SPDX-FileCopyrightText: 2019 Volker Krause <vkrause@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include "palette.h"

#include <KTextTemplate/MetaType>
#include <QObject>

#include <QPalette>
using namespace Qt::Literals::StringLiterals;

#define ROLE(R)                                                                                                                                                \
    {                                                                                                                                                          \
#R, QPalette::R                                                                                                                                        \
    }

static const struct {
    const char *name;
    QPalette::ColorRole role;
} color_roles[] = {
    ROLE(AlternateBase),   ROLE(Base),  ROLE(BrightText),  ROLE(Button),      ROLE(ButtonText), ROLE(Dark),       ROLE(Highlight),
    ROLE(HighlightedText), ROLE(Light), ROLE(Link),        ROLE(LinkVisited), ROLE(Mid),        ROLE(Midlight),   ROLE(PlaceholderText),
    ROLE(Shadow),          ROLE(Text),  ROLE(ToolTipBase), ROLE(ToolTipText), ROLE(Window),     ROLE(WindowText),
};
KTEXTTEMPLATE_BEGIN_LOOKUP(QPalette)
auto group = QPalette::Inactive;
auto roleName = property;

if (property.startsWith("active"_L1)) {
    roleName = property.mid(6);
    group = QPalette::Active;
} else if (property.startsWith("disabled"_L1)) {
    roleName = property.mid(8);
    group = QPalette::Disabled;
} else if (property.startsWith("inactive"_L1)) {
    roleName = property.mid(8);
    group = QPalette::Inactive;
}

for (const auto &role : color_roles) {
    if (roleName.compare(QLatin1StringView(role.name), Qt::CaseInsensitive) == 0) {
        return object.color(group, role.role);
    }
}
return {};
KTEXTTEMPLATE_END_LOOKUP

void Palette::registerMetaType()
{
    KTextTemplate::registerMetaType<QPalette>();
}
