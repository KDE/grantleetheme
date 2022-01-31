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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    , Grantlee::TagLibraryInterface()
#else
    , KTextTemplate::TagLibraryInterface()
#endif
{
    Color::registerMetaType();
    ColorScheme::registerMetaType();
    Palette::registerMetaType();
}

KDEGrantleePlugin::~KDEGrantleePlugin() = default;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
QHash<QString, Grantlee::AbstractNodeFactory *> KDEGrantleePlugin::nodeFactories(const QString &name)
#else
QHash<QString, KTextTemplate::AbstractNodeFactory *> KDEGrantleePlugin::nodeFactories(const QString &name)
#endif
{
    Q_UNUSED(name)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QHash<QString, Grantlee::AbstractNodeFactory *> nodeFactories;
#else
    QHash<QString, KTextTemplate::AbstractNodeFactory *> nodeFactories;
#endif
    nodeFactories[QStringLiteral("colorMix")] = new ColorMixTag();
    nodeFactories[QStringLiteral("icon")] = new IconTag();

    return nodeFactories;
}
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
QHash<QString, Grantlee::Filter *> KDEGrantleePlugin::filters(const QString &name)
#else
QHash<QString, KTextTemplate::Filter *> KDEGrantleePlugin::filters(const QString &name)
#endif
{
    Q_UNUSED(name)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QHash<QString, Grantlee::Filter *> filters;
#else
    QHash<QString, KTextTemplate::Filter *> filters;
#endif
    filters.insert(QStringLiteral("colorHexRgb"), new ColorHexRgbFilter());
    filters.insert(QStringLiteral("colorCssRgba"), new ColorCssRgbaFilter());
    filters.insert(QStringLiteral("colorLighter"), new ColorLighterFilter());
    filters.insert(QStringLiteral("colorDarker"), new ColorDarkerFilter());
    filters.insert(QStringLiteral("colorSetAlpha"), new ColorSetAlphaFilter());
    return filters;
}
