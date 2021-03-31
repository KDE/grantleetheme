/*
 * SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */

#pragma once
#include "grantlee/templateloader.h"
#include "grantleetheme_export.h"
namespace GrantleeTheme
{
/**
 * @brief The QtResourceTemplateLoader class
 * @author Laurent montel <montel@kde.org>
 */
class GRANTLEETHEME_EXPORT QtResourceTemplateLoader : public Grantlee::FileSystemTemplateLoader
{
public:
    QtResourceTemplateLoader(const QSharedPointer<Grantlee::AbstractLocalizer> localizer = QSharedPointer<Grantlee::AbstractLocalizer>());

    Q_REQUIRED_RESULT Grantlee::Template loadByName(const QString &fileName, const Grantlee::Engine *engine) const override;
    Q_REQUIRED_RESULT bool canLoadTemplate(const QString &name) const override;
};
}
