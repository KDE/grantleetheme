/*
 * Copyright (C) 2019 Volker Krause <vkrause@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "color.h"

#include <grantlee/exception.h>
#include <grantlee/metatype.h>
#include <grantlee/parser.h>
#include <grantlee/variable.h>

#include <KColorUtils>
#include <QColor>
#include <QDebug>

static QColor inputToColor(const QVariant &v)
{
    if (v.canConvert<Grantlee::SafeString>()) {
        return QColor(v.value<Grantlee::SafeString>().get());
    }
    return v.value<QColor>();
}

static QString rgbaString(const QColor &c)
{
    return QLatin1String("rgba(")
           + QString::number(c.red()) + QLatin1String(", ")
           + QString::number(c.green()) + QLatin1String(", ")
           + QString::number(c.blue()) + QLatin1String(", ")
           + QString::number(c.alphaF()) + QLatin1Char(')');
}

#define COLOR_PROP(name) if (property == QLatin1String(#name)) { return object.name(); }

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
    : Grantlee::AbstractNodeFactory(parent)
{
}

ColorMixTag::~ColorMixTag() = default;

Grantlee::Node *ColorMixTag::getNode(const QString &tagContent, Grantlee::Parser *p) const
{
    Q_UNUSED(p);
    const auto parts = smartSplit(tagContent);
    if (parts.size() != 4 && parts.size() != 6) {
        throw Grantlee::Exception(Grantlee::TagSyntaxError, QStringLiteral("colormix tag needs 3 or 5 arguments"));
    }

    bool ok = false;
    const auto ratio = parts.at(3).toDouble(&ok);
    if (!ok) {
        throw Grantlee::Exception(Grantlee::TagSyntaxError, QStringLiteral("colormix: invalid ratio"));
    }

    QString varName;
    if (parts.size() == 6) {
        if (parts.at(4) != QLatin1String("as")) {
            throw Grantlee::Exception(Grantlee::TagSyntaxError, QStringLiteral("colormix: syntax error"));
        }
        varName = parts.at(5);
    }

    return new ColorMixNode(parts.at(1), parts.at(2), ratio, varName);
}

ColorMixNode::ColorMixNode(const QString &color1Name, const QString &color2Name, double ratio, const QString &varName, QObject *parent)
    : Grantlee::Node(parent)
    , m_color1Name(color1Name)
    , m_color2Name(color2Name)
    , m_varName(varName)
    , m_ratio(ratio)
{
}

ColorMixNode::~ColorMixNode() = default;

static QColor resolveColor(const QString &name, Grantlee::Context *c)
{
    if (name.startsWith(QLatin1Char('"')) && name.endsWith(QLatin1Char('"'))) {
        return QColor(name.midRef(1, name.size() - 2));
    }

    const auto val = Grantlee::Variable(name).resolve(c);
    return val.value<QColor>();
}

void ColorMixNode::render(Grantlee::OutputStream *stream, Grantlee::Context *c) const
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
