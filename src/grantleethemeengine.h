/*
  SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once

#include <KTextTemplate/Engine>
#include <QSharedPointer>

#include "grantleetheme_export.h"

namespace GrantleeTheme
{
class GrantleeKi18nLocalizer;
class EnginePrivate;
/*!
 * \class GrantleeTheme::Engine
 * \inmodule Engine
 * \inheaderfile GrantleeTheme/Engine
 *
 * \brief The Engine class.
 */
class GRANTLEETHEME_EXPORT Engine : public KTextTemplate::Engine
{
    Q_OBJECT

public:
    /*!
     */
    explicit Engine(QObject *parent = nullptr);
    /*!
     */
    ~Engine() override;

    /*!
     */
    [[nodiscard]] QSharedPointer<GrantleeKi18nLocalizer> localizer() const;

private:
    std::unique_ptr<EnginePrivate> const d;
};
}
