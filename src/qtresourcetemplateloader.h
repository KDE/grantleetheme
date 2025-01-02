/*
 * SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */

#pragma once
#include <KTextTemplate/TemplateLoader>
#include <QObject>

#include "grantleetheme_export.h"
namespace GrantleeTheme
{
/**
 * @brief The QtResourceTemplateLoader class
 * @author Laurent montel <montel@kde.org>
 */
class GRANTLEETHEME_EXPORT QtResourceTemplateLoader : public KTextTemplate::FileSystemTemplateLoader
{
public:
    QtResourceTemplateLoader(const QSharedPointer<KTextTemplate::AbstractLocalizer> localizer = QSharedPointer<KTextTemplate::AbstractLocalizer>());
    [[nodiscard]] KTextTemplate::Template loadByName(const QString &fileName, const KTextTemplate::Engine *engine) const override;

    [[nodiscard]] bool canLoadTemplate(const QString &name) const override;
};
}
