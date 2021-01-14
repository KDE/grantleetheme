/*
 * SPDX-FileCopyrightText: 2015 Daniel Vrátil <dvratil@redhat.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */

#include "kdegrantleeplugin.h"
#include "color.h"
#include "colorscheme.h"
#include "icon.h"
#include "palette.h"

KDEGrantleePlugin::KDEGrantleePlugin(QObject *parent)
    : QObject(parent)
    , Grantlee::TagLibraryInterface()
{
    Color::registerMetaType();
    ColorScheme::registerMetaType();
    Palette::registerMetaType();
}

KDEGrantleePlugin::~KDEGrantleePlugin()
{
}

QHash<QString, Grantlee::AbstractNodeFactory *> KDEGrantleePlugin::nodeFactories(const QString &name)
{
    Q_UNUSED(name)

    QHash<QString, Grantlee::AbstractNodeFactory *> nodeFactories;
    nodeFactories[QStringLiteral("colorMix")] = new ColorMixTag();
    nodeFactories[QStringLiteral("icon")] = new IconTag();

    return nodeFactories;
}

QHash<QString, Grantlee::Filter *> KDEGrantleePlugin::filters(const QString &name)
{
    Q_UNUSED(name)
    QHash<QString, Grantlee::Filter *> filters;
    filters.insert(QStringLiteral("colorHexRgb"), new ColorHexRgbFilter());
    filters.insert(QStringLiteral("colorCssRgba"), new ColorCssRgbaFilter());
    filters.insert(QStringLiteral("colorLighter"), new ColorLighterFilter());
    filters.insert(QStringLiteral("colorDarker"), new ColorDarkerFilter());
    filters.insert(QStringLiteral("colorSetAlpha"), new ColorSetAlphaFilter());
    return filters;
}
