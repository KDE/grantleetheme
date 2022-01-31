/*
  SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "grantleethemeengine.h"
#include "grantleeki18nlocalizer.h"

#include <config-grantleetheme.h>

using namespace GrantleeTheme;

class GrantleeTheme::EnginePrivate
{
public:
    EnginePrivate() = default;

    ~EnginePrivate() = default;

    QWeakPointer<GrantleeKi18nLocalizer> localizer;
};

Engine::Engine(QObject *parent)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    : Grantlee::Engine(parent)
#else
    : KTextTemplate::Engine(parent)
#endif
    , d(new GrantleeTheme::EnginePrivate)
{
    addPluginPath(QStringLiteral(GRANTLEE_PLUGIN_INSTALL_DIR));
    addDefaultLibrary(QStringLiteral("grantlee_i18ntags"));
    addDefaultLibrary(QStringLiteral("kde_grantlee_plugin"));
    addDefaultLibrary(QStringLiteral("grantlee_scriptabletags"));
    setSmartTrimEnabled(true);
}

Engine::~Engine() = default;

QSharedPointer<GrantleeKi18nLocalizer> Engine::localizer() const
{
    auto loc = d->localizer.toStrongRef();
    if (!loc) {
        loc.reset(new GrantleeKi18nLocalizer());
        d->localizer = loc.toWeakRef();
    }
    return loc;
}
