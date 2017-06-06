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

#ifndef GRANTLEETHEMEENGINE_H
#define GRANTLEETHEMEENGINE_H

#include <grantlee/engine.h>
#include <QSharedPointer>

#include "grantleetheme_export.h"

namespace GrantleeTheme {
class GrantleeKi18nLocalizer;
class EnginePrivate;
class GRANTLEETHEME_EXPORT Engine : public Grantlee::Engine
{
    Q_OBJECT

public:
    explicit Engine(QObject *parent = nullptr);
    ~Engine() override;

    QSharedPointer<GrantleeKi18nLocalizer> localizer() const;

private:
    EnginePrivate *const d;
};
}

#endif
