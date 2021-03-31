/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once

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

