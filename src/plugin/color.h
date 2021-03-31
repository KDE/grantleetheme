/*
 * SPDX-FileCopyrightText: 2019 Volker Krause <vkrause@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#pragma once

#include <grantlee/filter.h>
#include <grantlee/node.h>

/**
 * @name colorHexRgb filter
 * @brief Provides colorName filter for converting a QColor to a color string.
 *
 * The syntax is:
 * @code
 * {{ myColor|colorHexRgb }}
 * @endcode
 */
class ColorHexRgbFilter : public Grantlee::Filter
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

/**
 * @name colorCssRgba filter
 * @brief Provides colorRgba filter for converting a QColor to a rgba() CSS color definition.
 *
 * The syntax is:
 * @code
 * {{ myColor|colorCssRgba }}
 * @endcode
 */
class ColorCssRgbaFilter : public Grantlee::Filter
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

/**
 * @name colorLighter filter
 * @brief Provides colorLighter filter for applying QColor::lighter to a color.
 *
 * The syntax is:
 * @code
 * {{ myColor|colorLighter:<factor> }}
 * @endcode
 */
class ColorLighterFilter : public Grantlee::Filter
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

/**
 * @name colorDarker filter
 * @brief Provides colorDarker filter for applying QColor::darker to a color.
 *
 * The syntax is:
 * @code
 * {{ myColor|colorDarker:<factor> }}
 * @endcode
 */
class ColorDarkerFilter : public Grantlee::Filter
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

/**
 * @name colorSetAlpha filter
 * @brief Provides colorSetAlpha filter for setting a fixed alpha value on the given color.
 *
 * The syntax is:
 * @code
 * {{ myColor|colorSetAlpha:<alpha-value-from-0-to-255> }}
 * @endcode
 */
class ColorSetAlphaFilter : public Grantlee::Filter
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

/**
 * @name colorMix tag
 * @brief Provides {% colorMix %} tag for mixing two colors
 *
 * The syntax is:
 * @code
 * {% colorMix "#rrggbb"|var-with-color "#rrggbb"|var-with-color <ratio> %}
 * @endcode
 *
 * The tag generates a rgba() CSS color definition.
 */
class ColorMixTag : public Grantlee::AbstractNodeFactory
{
    Q_OBJECT
public:
    explicit ColorMixTag(QObject *parent = nullptr);
    ~ColorMixTag() override;
    Grantlee::Node *getNode(const QString &tagContent, Grantlee::Parser *p) const override;
};

class ColorMixNode : public Grantlee::Node
{
    Q_OBJECT
public:
    explicit ColorMixNode(const QString &color1Name, const QString &color2Name, double ratio, const QString &varName, QObject *parent = nullptr);
    ~ColorMixNode() override;
    void render(Grantlee::OutputStream *stream, Grantlee::Context *c) const override;

private:
    QString m_color1Name;
    QString m_color2Name;
    QString m_varName;
    double m_ratio;
};

namespace Color
{
void registerMetaType();
}

