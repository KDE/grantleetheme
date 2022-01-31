/*
 * SPDX-FileCopyrightText: 2019 Volker Krause <vkrause@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include "colorscheme.h"
#include <QObject>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <grantlee/metatype.h>
#else
#include <KTextTemplate/metatype.h>
#endif

#include <KColorScheme>

#define PROP_IMPL(PROP, METHOD)                                                                                                                                \
    if (QString::compare(property, QLatin1String(#PROP), Qt::CaseInsensitive) == 0) {                                                                          \
        return object.METHOD(KColorScheme::PROP).color();                                                                                                      \
    }
#define BACKGROUND_PROP(PROP) PROP_IMPL(PROP, background)
#define FOREGROUND_PROP(PROP) PROP_IMPL(PROP, foreground)
#define DECORATION_PROP(PROP) PROP_IMPL(PROP, decoration)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
GRANTLEE_BEGIN_LOOKUP(KColorScheme)
#else
KTEXTTEMPLATE_BEGIN_LOOKUP(KColorScheme)
#endif
BACKGROUND_PROP(NormalBackground)
BACKGROUND_PROP(AlternateBackground)
BACKGROUND_PROP(ActiveBackground)
BACKGROUND_PROP(LinkBackground)
BACKGROUND_PROP(VisitedBackground)
BACKGROUND_PROP(NegativeBackground)
BACKGROUND_PROP(NeutralBackground)
BACKGROUND_PROP(PositiveBackground)

FOREGROUND_PROP(NormalText)
FOREGROUND_PROP(InactiveText)
FOREGROUND_PROP(ActiveText)
FOREGROUND_PROP(LinkText)
FOREGROUND_PROP(VisitedText)
FOREGROUND_PROP(NegativeText)
FOREGROUND_PROP(NeutralText)
FOREGROUND_PROP(PositiveText)

DECORATION_PROP(FocusColor)
DECORATION_PROP(HoverColor)

return {};
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
GRANTLEE_END_LOOKUP
#else
KTEXTTEMPLATE_END_LOOKUP
#endif

void ColorScheme::registerMetaType()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    Grantlee::registerMetaType<KColorScheme>();
#else
    KTextTemplate::registerMetaType<KColorScheme>();
#endif
}
