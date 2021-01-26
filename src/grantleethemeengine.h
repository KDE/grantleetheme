/*
  SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef GRANTLEETHEMEENGINE_H
#define GRANTLEETHEMEENGINE_H

#include <QSharedPointer>
#include <grantlee/engine.h>

#include "grantleetheme_export.h"

namespace GrantleeTheme
{
class GrantleeKi18nLocalizer;
class EnginePrivate;
/**
 * @brief The Engine class
 */
class GRANTLEETHEME_EXPORT Engine : public Grantlee::Engine
{
    Q_OBJECT

public:
    explicit Engine(QObject *parent = nullptr);
    ~Engine() override;

    Q_REQUIRED_RESULT QSharedPointer<GrantleeKi18nLocalizer> localizer() const;

private:
    EnginePrivate *const d;
};
}

#endif
