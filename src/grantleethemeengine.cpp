/*
  Copyright (c) 2016 Daniel Vrátil <dvratil@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "grantleethemeengine.h"
#include "grantleeki18nlocalizer.h"

#include "config-grantleetheme.h"

using namespace GrantleeTheme;

class GrantleeTheme::EnginePrivate
{
public:
    EnginePrivate()
    {
    }

    ~EnginePrivate()
    {
    }

    QWeakPointer<GrantleeKi18nLocalizer> localizer;
};


Engine::Engine(QObject *parent)
    : Grantlee::Engine(parent)
    , d(new GrantleeTheme::EnginePrivate)
{
    addPluginPath(QStringLiteral(GRANTLEE_PLUGIN_INSTALL_DIR));
    addDefaultLibrary(QStringLiteral("grantlee_i18ntags"));
    addDefaultLibrary(QStringLiteral("kde_grantlee_plugin"));
    addDefaultLibrary(QStringLiteral("grantlee_scriptabletags"));
    setSmartTrimEnabled(true);
}

Engine::~Engine()
{
    delete d;
}

QSharedPointer<GrantleeKi18nLocalizer> Engine::localizer() const
{
    auto loc = d->localizer.toStrongRef();
    if (!loc) {
        loc.reset(new GrantleeKi18nLocalizer());
        d->localizer = loc.toWeakRef();
    }
    return loc;
}