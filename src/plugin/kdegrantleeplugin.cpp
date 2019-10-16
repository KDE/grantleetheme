/*
 * Copyright (C) 2015  Daniel Vrátil <dvratil@redhat.com>
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
    Q_UNUSED(name);

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
