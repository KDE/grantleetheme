/*
  SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once

#include <QSharedPointer>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <grantlee/engine.h>
#else
#include <KTextTemplate/engine.h>
#endif

#include "grantleetheme_export.h"

namespace GrantleeTheme
{
class GrantleeKi18nLocalizer;
class EnginePrivate;
/**
 * @brief The Engine class
 */
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class GRANTLEETHEME_EXPORT Engine : public Grantlee::Engine
#else
class GRANTLEETHEME_EXPORT Engine : public KTextTemplate::Engine
#endif
{
    Q_OBJECT

public:
    explicit Engine(QObject *parent = nullptr);
    ~Engine() override;

    Q_REQUIRED_RESULT QSharedPointer<GrantleeKi18nLocalizer> localizer() const;

private:
    std::unique_ptr<EnginePrivate> const d;
};
}
