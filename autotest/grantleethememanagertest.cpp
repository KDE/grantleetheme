/*
  Copyright (c) 2016 David Faure <faure@kde.org>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "grantleethememanager.h"

#include <qtest.h>
#include <QDir>
#include <QStandardPaths>
#include <QMenu>
#include <QDebug>

#include <KConfigGroup>
#include <KSharedConfig>
#include <KActionCollection>
#include <KActionMenu>

class GrantleeThemeManagerTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void updateActionList();

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
    GrantleeTheme::ThemeManager *manager(new GrantleeTheme::ThemeManager(QStringLiteral("Stuff"), QStringLiteral("filename.testdesktop"), &coll, QStringLiteral("themes")));
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

    delete manager; // must be deleted while the action group still exists
}

QTEST_MAIN(GrantleeThemeManagerTest)
#include "grantleethememanagertest.moc"
