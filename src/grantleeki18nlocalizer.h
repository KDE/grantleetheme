/*
 * SPDX-FileCopyrightText: 2015 Daniel Vrátil <dvratil@redhat.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */

#ifndef GRANTLEEKI18NLOCALIZER_H
#define GRANTLEEKI18NLOCALIZER_H

#include "grantleetheme_export.h"
#include <grantlee/qtlocalizer.h>

#include <QLocale>
#include <QVariantHash>

class KLocalizedString;
namespace GrantleeTheme {
/**
 * @brief The GrantleeKi18nLocalizer class
 */
class GRANTLEETHEME_EXPORT GrantleeKi18nLocalizer : public Grantlee::QtLocalizer
{
public:
    explicit GrantleeKi18nLocalizer();
    ~GrantleeKi18nLocalizer() override;

    // Only reimplement string localization to use KLocalizedString instead of
    // tr(), the remaining methods use QLocale internally, so we can reuse them
    Q_REQUIRED_RESULT QString localizeContextString(const QString &string, const QString &context, const QVariantList &arguments) const override;
    Q_REQUIRED_RESULT QString localizeString(const QString &string, const QVariantList &arguments) const override;
    Q_REQUIRED_RESULT QString localizePluralContextString(const QString &string, const QString &pluralForm, const QString &context, const QVariantList &arguments) const override;
    Q_REQUIRED_RESULT QString localizePluralString(const QString &string, const QString &pluralForm, const QVariantList &arguments) const override;

    // Only exception, Grantlee's implementation is not using QLocale for this
    // for some reason
    Q_REQUIRED_RESULT QString localizeMonetaryValue(qreal value, const QString &currentCode) const override;

    Q_REQUIRED_RESULT QString currentLocale() const override;

    void setApplicationDomain(const QByteArray &domain);
private:
    QString processArguments(const KLocalizedString &str, const QVariantList &arguments) const;
    QByteArray mApplicationDomain;
};
}

#endif // GRANTLEEKI18NLOCALIZER_H
