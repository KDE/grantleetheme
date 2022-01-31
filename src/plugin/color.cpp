/*
 * SPDX-FileCopyrightText: 2019 Volker Krause <vkrause@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include "color.h"
#include <QObject>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <grantlee/exception.h>
#include <grantlee/metatype.h>
#include <grantlee/parser.h>
#include <grantlee/variable.h>
#else
#include <KTextTemplate/exception.h>
#include <KTextTemplate/metatype.h>
#include <KTextTemplate/parser.h>
#include <KTextTemplate/variable.h>
#endif

#include <KColorUtils>
#include <QColor>

static QColor inputToColor(const QVariant &v)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if (v.canConvert<Grantlee::SafeString>()) {
        return QColor(v.value<Grantlee::SafeString>().get());
    }
#else
    if (v.canConvert<KTextTemplate::SafeString>()) {
        return QColor(v.value<KTextTemplate::SafeString>().get());
    }
#endif
    return v.value<QColor>();
}

static QString rgbaString(const QColor &c)
{
    return QLatin1String("rgba(") + QString::number(c.red()) + QLatin1String(", ") + QString::number(c.green()) + QLatin1String(", ")
        + QString::number(c.blue()) + QLatin1String(", ") + QString::number(c.alphaF()) + QLatin1Char(')');
}

#define COLOR_PROP(name)                                                                                                                                       \
    if (property == QLatin1String(#name)) {                                                                                                                    \
        return object.name();                                                                                                                                  \
    }

GRANTLEE_BEGIN_LOOKUP(QColor)
COLOR_PROP(red)
COLOR_PROP(green)
COLOR_PROP(blue)
COLOR_PROP(alpha)
if (property == QLatin1String("hexRgb")) {
    return object.name();
}
if (property == QLatin1String("cssRgba")) {
    return rgbaString(object);
}
return {};
GRANTLEE_END_LOOKUP

void Color::registerMetaType()
{
    Grantlee::registerMetaType<QColor>();
}

QVariant ColorHexRgbFilter::doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const
{
    Q_UNUSED(arg)
    Q_UNUSED(autoescape)

    const auto color = inputToColor(input);
    return color.name();
}

QVariant ColorCssRgbaFilter::doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const
{
    Q_UNUSED(arg)
    Q_UNUSED(autoescape)

    const auto color = inputToColor(input);
    return rgbaString(color);
}

QVariant ColorLighterFilter::doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const
{
    Q_UNUSED(autoescape)

    const auto color = inputToColor(input);
    const auto factor = arg.toInt();
    return color.lighter(factor);
}

QVariant ColorDarkerFilter::doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const
{
    Q_UNUSED(autoescape)

    const auto color = inputToColor(input);
    const auto factor = arg.toInt();
    return color.darker(factor);
}

QVariant ColorSetAlphaFilter::doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const
{
    Q_UNUSED(autoescape)

    auto color = inputToColor(input);
    color.setAlpha(arg.toInt());
    return color;
}

ColorMixTag::ColorMixTag(QObject *parent)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    : Grantlee::AbstractNodeFactory(parent)
#else
    : KTextTemplate::AbstractNodeFactory(parent)
#endif
{
}

ColorMixTag::~ColorMixTag() = default;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
Grantlee::Node *ColorMixTag::getNode(const QString &tagContent, Grantlee::Parser *p) const
#else
KTextTemplate::Node *ColorMixTag::getNode(const QString &tagContent, KTextTemplate::Parser *p) const
#endif
{
    Q_UNUSED(p)
    const auto parts = smartSplit(tagContent);
    if (parts.size() != 4 && parts.size() != 6) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        throw Grantlee::Exception(Grantlee::TagSyntaxError, QStringLiteral("colormix tag needs 3 or 5 arguments"));
#else
        throw KTextTemplate::Exception(KTextTemplate::TagSyntaxError, QStringLiteral("colormix tag needs 3 or 5 arguments"));
#endif
    }

    bool ok = false;
    const auto ratio = parts.at(3).toDouble(&ok);
    if (!ok) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        throw Grantlee::Exception(Grantlee::TagSyntaxError, QStringLiteral("colormix: invalid ratio"));
#else
        throw KTextTemplate::Exception(KTextTemplate::TagSyntaxError, QStringLiteral("colormix: invalid ratio"));
#endif
    }

    QString varName;
    if (parts.size() == 6) {
        if (parts.at(4) != QLatin1String("as")) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            throw Grantlee::Exception(Grantlee::TagSyntaxError, QStringLiteral("colormix: syntax error"));
#else
            throw KTextTemplate::Exception(KTextTemplate::TagSyntaxError, QStringLiteral("colormix: syntax error"));
#endif
        }
        varName = parts.at(5);
    }

    return new ColorMixNode(parts.at(1), parts.at(2), ratio, varName);
}

ColorMixNode::ColorMixNode(const QString &color1Name, const QString &color2Name, double ratio, const QString &varName, QObject *parent)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    : Grantlee::Node(parent)
#else
    : KTextTemplate::Node(parent)
#endif
    , m_color1Name(color1Name)
    , m_color2Name(color2Name)
    , m_varName(varName)
    , m_ratio(ratio)
{
}

ColorMixNode::~ColorMixNode() = default;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
static QColor resolveColor(const QString &name, Grantlee::Context *c)
#else
static QColor resolveColor(const QString &name, KTextTemplate::Context *c)
#endif
{
    if (name.startsWith(QLatin1Char('"')) && name.endsWith(QLatin1Char('"'))) {
        return QColor(QStringView(name).mid(1, name.size() - 2));
    }
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    const auto val = Grantlee::Variable(name).resolve(c);
#else
    const auto val = KTextTemplate::Variable(name).resolve(c);
#endif
    return val.value<QColor>();
}
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
void ColorMixNode::render(Grantlee::OutputStream *stream, Grantlee::Context *c) const
#else
void ColorMixNode::render(KTextTemplate::OutputStream *stream, KTextTemplate::Context *c) const
#endif
{
    const auto col1 = resolveColor(m_color1Name, c);
    const auto col2 = resolveColor(m_color2Name, c);
    const auto result = KColorUtils::mix(col1, col2, m_ratio);
    if (!m_varName.isEmpty()) {
        c->insert(m_varName, QVariant::fromValue(result));
    } else {
        (*stream) << rgbaString(result);
    }
}
