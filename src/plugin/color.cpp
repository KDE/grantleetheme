/*
 * SPDX-FileCopyrightText: 2019 Volker Krause <vkrause@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include "color.h"
#include <KTextTemplate/Exception>
#include <KTextTemplate/MetaType>
#include <KTextTemplate/Parser>
#include <KTextTemplate/Variable>

#include <KColorUtils>
#include <QColor>

static QColor inputToColor(const QVariant &v)
{
    if (v.canConvert<KTextTemplate::SafeString>()) {
        return QColor(v.value<KTextTemplate::SafeString>().get());
    }
    return v.value<QColor>();
}

static QString rgbaString(const QColor &c)
{
    return QLatin1StringView("rgba(") + QString::number(c.red()) + QLatin1String(", ") + QString::number(c.green()) + QLatin1String(", ")
        + QString::number(c.blue()) + QLatin1StringView(", ") + QString::number(c.alphaF()) + QLatin1Char(')');
}

#define COLOR_PROP(name)                                                                                                                                       \
    if (property == QLatin1StringView(#name)) {                                                                                                                \
        return object.name();                                                                                                                                  \
    }
KTEXTTEMPLATE_BEGIN_LOOKUP(QColor)
COLOR_PROP(red)
COLOR_PROP(green)
COLOR_PROP(blue)
COLOR_PROP(alpha)
if (property == QLatin1StringView("hexRgb")) {
    return object.name();
}
if (property == QLatin1StringView("cssRgba")) {
    return rgbaString(object);
}
return {};
KTEXTTEMPLATE_END_LOOKUP
void Color::registerMetaType()
{
    KTextTemplate::registerMetaType<QColor>();
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
    : KTextTemplate::AbstractNodeFactory(parent)
{
}

ColorMixTag::~ColorMixTag() = default;
KTextTemplate::Node *ColorMixTag::getNode(const QString &tagContent, KTextTemplate::Parser *p) const
{
    Q_UNUSED(p)
    const auto parts = smartSplit(tagContent);
    if (parts.size() != 4 && parts.size() != 6) {
        throw KTextTemplate::Exception(KTextTemplate::TagSyntaxError, QStringLiteral("colormix tag needs 3 or 5 arguments"));
    }

    bool ok = false;
    const auto ratio = parts.at(3).toDouble(&ok);
    if (!ok) {
        throw KTextTemplate::Exception(KTextTemplate::TagSyntaxError, QStringLiteral("colormix: invalid ratio"));
    }

    QString varName;
    if (parts.size() == 6) {
        if (parts.at(4) != QLatin1StringView("as")) {
            throw KTextTemplate::Exception(KTextTemplate::TagSyntaxError, QStringLiteral("colormix: syntax error"));
        }
        varName = parts.at(5);
    }

    return new ColorMixNode(parts.at(1), parts.at(2), ratio, varName);
}

ColorMixNode::ColorMixNode(const QString &color1Name, const QString &color2Name, double ratio, const QString &varName, QObject *parent)
    : KTextTemplate::Node(parent)
    , m_color1Name(color1Name)
    , m_color2Name(color2Name)
    , m_varName(varName)
    , m_ratio(ratio)
{
}

ColorMixNode::~ColorMixNode() = default;
static QColor resolveColor(const QString &name, KTextTemplate::Context *c)
{
    if (name.startsWith(QLatin1Char('"')) && name.endsWith(QLatin1Char('"'))) {
        return QColor(QStringView(name).mid(1, name.size() - 2));
    }
    const auto val = KTextTemplate::Variable(name).resolve(c);
    return val.value<QColor>();
}
void ColorMixNode::render(KTextTemplate::OutputStream *stream, KTextTemplate::Context *c) const
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

#include "moc_color.cpp"
