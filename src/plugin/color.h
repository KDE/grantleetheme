/*
 * SPDX-FileCopyrightText: 2019 Volker Krause <vkrause@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#pragma once
#include <QObject>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <grantlee/filter.h>
#include <grantlee/node.h>
#else
#include <KTextTemplate/filter.h>
#include <KTextTemplate/node.h>
#endif

/**
 * @name colorHexRgb filter
 * @brief Provides colorName filter for converting a QColor to a color string.
 *
 * The syntax is:
 * @code
 * {{ myColor|colorHexRgb }}
 * @endcode
 */
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class ColorHexRgbFilter : public Grantlee::Filter
#else
class ColorHexRgbFilter : public KTextTemplate::Filter
#endif
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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class ColorCssRgbaFilter : public Grantlee::Filter
#else
class ColorCssRgbaFilter : public KTextTemplate::Filter
#endif
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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class ColorLighterFilter : public Grantlee::Filter
#else
class ColorLighterFilter : public KTextTemplate::Filter
#endif
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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class ColorDarkerFilter : public Grantlee::Filter
#else
class ColorDarkerFilter : public KTextTemplate::Filter
#endif
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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class ColorSetAlphaFilter : public Grantlee::Filter
#else
class ColorSetAlphaFilter : public KTextTemplate::Filter
#endif
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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class ColorMixTag : public Grantlee::AbstractNodeFactory
#else
class ColorMixTag : public KTextTemplate::AbstractNodeFactory
#endif
{
    Q_OBJECT
public:
    explicit ColorMixTag(QObject *parent = nullptr);
    ~ColorMixTag() override;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    Grantlee::Node *getNode(const QString &tagContent, Grantlee::Parser *p) const override;
#else
    KTextTemplate::Node *getNode(const QString &tagContent, KTextTemplate::Parser *p) const override;
#endif
};

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class ColorMixNode : public Grantlee::Node
#else
class ColorMixNode : public KTextTemplate::Node
#endif
{
    Q_OBJECT
public:
    explicit ColorMixNode(const QString &color1Name, const QString &color2Name, double ratio, const QString &varName, QObject *parent = nullptr);
    ~ColorMixNode() override;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    void render(Grantlee::OutputStream *stream, Grantlee::Context *c) const override;
#else
    void render(KTextTemplate::OutputStream *stream, KTextTemplate::Context *c) const override;
#endif

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
