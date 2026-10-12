/*
    SPDX-FileCopyrightText: 2015 Daniel Vrátil <dvratil@redhat.com>
    SPDX-FileCopyrightText: 2026 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include "format.h"

#include <KFormat>
#include <KTextTemplate/SafeString>

#include <QDateTime>
#include <QMetaEnum>

using namespace Qt::Literals;

QVariant KFormatDateTimeFilter::doFilter(const QVariant &input, const QVariant &argument, [[maybe_unused]] bool autoescape) const
{
    if (input.userType() != QMetaType::QDateTime) {
        return QString();
    }
    const auto dt = input.toDateTime();
    const auto arguments = argument.value<KTextTemplate::SafeString>().get().split(u',');

    QLocale::FormatType format = QLocale::ShortFormat;
    if (arguments.contains("LongFormat"_L1)) {
        format = QLocale::LongFormat;
    }

#if KCOREADDONS_VERSION >= QT_VERSION_CHECK(6, 31, 0)
    KFormat::TimeFormatOptions opts = {};
    const auto me = QMetaEnum::fromType<KFormat::TimeFormatOptions>();
    for (int i = 0; i < me.keyCount(); ++i) {
        if (!arguments.contains(QLatin1StringView(me.key(i)))) {
            continue;
        }
        opts |= static_cast<KFormat::TimeFormatOptions>(me.value(i));
    }

    KFormat fmt(QLocale(context()->localizer()->currentLocale()));
    return KTextTemplate::SafeString(fmt.formatDateTime(dt, format, opts));
#else
    return context()->localizer()->localizeDateTime(dt, format);
#endif
}
