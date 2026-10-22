/*
    SPDX-FileCopyrightText: 2026 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <KTextTemplate/Filter>

class KFormatDateTimeFilter : public KTextTemplate::Filter
{
public:
    explicit KFormatDateTimeFilter() = default;
    QVariant doFilter(const QVariant &input, const QVariant &argument = QVariant(), bool autoescape = false) const override;
    bool isSafe() const override
    {
        return true;
    }

private:
    Q_DISABLE_COPY(KFormatDateTimeFilter)
};
