/*
  Copyright (c) 2014-2018 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef GRANTLEETHEMETEST_H
#define GRANTLEETHEMETEST_H

#include <QObject>

class GrantleeThemeTest : public QObject
{
    Q_OBJECT
public:
    explicit GrantleeThemeTest(QObject *parent = nullptr);
    ~GrantleeThemeTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldInvalidWhenPathIsNotValid();
    void shouldLoadTheme_data();
    void shouldLoadTheme();

    void testRenderTemplate_data();
    void testRenderTemplate();

private:
    bool validateHtml(const QString &path, const QString &name, const QString &html);
    bool compareHtml(const QString &path, const QString &name);
};

#endif // GRANTLEETHEMETEST_H
