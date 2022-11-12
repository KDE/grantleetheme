/*
 * SPDX-FileCopyrightText: 2019 Volker Krause <vkrause@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include "palette.h"
#include <QObject>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <grantlee/metatype.h>
#else
#include <KTextTemplate/MetaType>
#endif

#include <QPalette>

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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
GRANTLEE_BEGIN_LOOKUP(QPalette)
#else
KTEXTTEMPLATE_BEGIN_LOOKUP(QPalette)
#endif
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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
GRANTLEE_END_LOOKUP
#else
KTEXTTEMPLATE_END_LOOKUP
#endif

void Palette::registerMetaType()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    Grantlee::registerMetaType<QPalette>();
#else
    KTextTemplate::registerMetaType<QPalette>();
#endif
}
