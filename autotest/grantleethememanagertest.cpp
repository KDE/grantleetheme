/*
  SPDX-FileCopyrightText: 2016 David Faure <faure@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "grantleethememanager.h"

#include <QMenu>
#include <QStandardPaths>
#include <qtest.h>

#include <KActionCollection>
#include <KActionMenu>
#include <KConfigGroup>
#include <KSharedConfig>

class GrantleeThemeManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit GrantleeThemeManagerTest(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

private Q_SLOTS:
    void initTestCase();
    void updateActionList();
    void destructionOrderTest();
};

void GrantleeThemeManagerTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);

    // Point the test to our dummy icon theme
    KConfigGroup cg(KSharedConfig::openConfig(), "Icons");
    cg.writeEntry("Theme", "dummyTheme");
    qputenv("XDG_DATA_DIRS", GRANTLEETHEME_DATA_DIR);
}

void GrantleeThemeManagerTest::updateActionList()
{
    KActionCollection coll(this);
    GrantleeTheme::ThemeManager *manager(
        new GrantleeTheme::ThemeManager(QStringLiteral("Stuff"), QStringLiteral("filename.testdesktop"), &coll, QStringLiteral("themes")));
    QCOMPARE(manager->themes().count(), 2);
    QVERIFY(!manager->actionForTheme()); // Bug? No "default" theme.

    QActionGroup actionGroup(this);
    manager->setActionGroup(&actionGroup);

    KActionMenu menu(this);
    manager->setThemeMenu(&menu);
    QCOMPARE(menu.menu()->actions().count(), 4); // 2 themes + separator + download

    KActionMenu menu2(this);
    manager->setThemeMenu(&menu2);
    QCOMPARE(menu2.menu()->actions().count(), 4);

    QVERIFY(QMetaObject::invokeMethod(manager, "directoryChanged"));
    QCOMPARE(menu2.menu()->actions().count(), 4);

    delete manager; // deleted while the action group still exists
}

void GrantleeThemeManagerTest::destructionOrderTest()
{
    KActionCollection coll(this);
    GrantleeTheme::ThemeManager *manager(
        new GrantleeTheme::ThemeManager(QStringLiteral("Stuff"), QStringLiteral("filename.testdesktop"), &coll, QStringLiteral("themes")));
    QCOMPARE(manager->themes().count(), 2);
    QVERIFY(!manager->actionForTheme()); // Bug? No "default" theme.

    auto *actionGroup = new QActionGroup(this);
    manager->setActionGroup(actionGroup);

    auto *menu = new KActionMenu(this);
    manager->setThemeMenu(menu);
    QCOMPARE(menu->menu()->actions().count(), 4); // 2 themes + separator + download

    auto *menu2 = new KActionMenu(this);
    manager->setThemeMenu(menu2);
    QCOMPARE(menu2->menu()->actions().count(), 4);

    QVERIFY(QMetaObject::invokeMethod(manager, "directoryChanged"));
    QCOMPARE(menu2->menu()->actions().count(), 4);

    manager->setThemeMenu(nullptr);
    delete menu;
    delete menu2;
    manager->setActionGroup(nullptr);
    delete actionGroup;
    delete manager; // deleted with the action group already deleted (as happens in kmail)
}

QTEST_MAIN(GrantleeThemeManagerTest)
#include "grantleethememanagertest.moc"
