/*
 * SPDX-FileCopyrightText: 2015 Daniel Vrátil <dvratil@redhat.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */

#pragma once
#include "grantleetheme_export.h"
#include <KTextTemplate/QtLocalizer>
#include <QObject>

#include <QLocale>
#include <QVariantHash>

class KLocalizedString;
namespace GrantleeTheme
{
/*!
 * \class GrantleeTheme::GrantleeKi18nLocalizer
 * \inmodule GrantleeTheme
 * \inheaderfile GrantleeTheme/GrantleeKi18nLocalizer
 *
 * \brief The GrantleeKi18nLocalizer class.
 */
class GRANTLEETHEME_EXPORT GrantleeKi18nLocalizer : public KTextTemplate::QtLocalizer
{
public:
    /*!
     * \brief Constructs a GrantleeKi18nLocalizer.
     */
    explicit GrantleeKi18nLocalizer();
    /*!
     * \brief Destroys the GrantleeKi18nLocalizer.
     */
    ~GrantleeKi18nLocalizer() override;

    // Only reimplement string localization to use KLocalizedString instead of
    // tr(), the remaining methods use QLocale internally, so we can reuse them
    /*!
     * \brief Localizes a string with context and arguments using KI18n.
     * \param string The string to localize
     * \param context The context for the string
     * \param arguments Arguments to substitute in the string
     * \return The localized string
     */
    [[nodiscard]] QString localizeContextString(const QString &string, const QString &context, const QVariantList &arguments) const override;
    /*!
     * \brief Localizes a string with arguments using KI18n.
     * \param string The string to localize
     * \param arguments Arguments to substitute in the string
     * \return The localized string
     */
    [[nodiscard]] QString localizeString(const QString &string, const QVariantList &arguments) const override;
    /*!
     * \brief Localizes a plural string with context and arguments using KI18n.
     * \param string The singular form of the string
     * \param pluralForm The plural form of the string
     * \param context The context for the string
     * \param arguments Arguments to substitute in the string
     * \return The localized string
     */
    [[nodiscard]] QString
    localizePluralContextString(const QString &string, const QString &pluralForm, const QString &context, const QVariantList &arguments) const override;
    /*!
     * \brief Localizes a plural string with arguments using KI18n.
     * \param string The singular form of the string
     * \param pluralForm The plural form of the string
     * \param arguments Arguments to substitute in the string
     * \return The localized string
     */
    [[nodiscard]] QString localizePluralString(const QString &string, const QString &pluralForm, const QVariantList &arguments) const override;

    // Only exception, Grantlee's implementation is not using QLocale for this
    // for some reason
    /*!
     * \brief Localizes a monetary value using KI18n.
     * \param value The monetary value to localize
     * \param currentCode The currency code
     * \return The localized monetary value as a string
     */
    [[nodiscard]] QString localizeMonetaryValue(qreal value, const QString &currentCode) const override;

    /*!
     * \brief Returns the current locale.
     * \return The current locale identifier
     */
    [[nodiscard]] QString currentLocale() const override;

    /*!
     * \brief Sets the application translation domain.
     * \param domain The translation domain to use
     */
    void setApplicationDomain(const QByteArray &domain);

private:
    [[nodiscard]] GRANTLEETHEME_NO_EXPORT QString processArguments(const KLocalizedString &str, const QVariantList &arguments) const;
    QByteArray mApplicationDomain;
};
}
