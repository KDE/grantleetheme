/*
  SPDX-FileCopyrightText: 2014-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "grantleethemetest.h"
#include "grantleetheme.h"

#include <QFile>
#include <QPalette>
#include <QProcess>
#include <QRegularExpression>
#include <QStandardPaths>
#include <qtest.h>

#include <KColorScheme>
#include <KConfigGroup>
#include <KSharedConfig>

GrantleeThemeTest::GrantleeThemeTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);

    // Point the test to our dummy icon theme
    KConfigGroup cg(KSharedConfig::openConfig(), "Icons");
    cg.writeEntry("Theme", "dummyTheme");
    qputenv("XDG_DATA_DIRS", GRANTLEETHEME_DATA_DIR);
}

GrantleeThemeTest::~GrantleeThemeTest() = default;

void GrantleeThemeTest::shouldHaveDefaultValue()
{
    GrantleeTheme::Theme theme;
    QVERIFY(theme.description().isEmpty());
    QVERIFY(theme.themeFilename().isEmpty());
    QVERIFY(theme.name().isEmpty());
    QVERIFY(theme.displayExtraVariables().isEmpty());
    QVERIFY(theme.dirName().isEmpty());
    QVERIFY(theme.absolutePath().isEmpty());
    QVERIFY(theme.author().isEmpty());
    QVERIFY(theme.authorEmail().isEmpty());
    QVERIFY(!theme.isValid());
}

void GrantleeThemeTest::shouldInvalidWhenPathIsNotValid()
{
    const QString themePath(QStringLiteral("/foo"));
    const QString dirName(QStringLiteral("name"));
    const QString defaultDesktopFileName(QStringLiteral("bla"));
    GrantleeTheme::Theme theme(themePath, dirName, defaultDesktopFileName);
    QVERIFY(theme.description().isEmpty());
    QVERIFY(theme.themeFilename().isEmpty());
    QVERIFY(theme.name().isEmpty());
    QVERIFY(theme.displayExtraVariables().isEmpty());
    QVERIFY(!theme.dirName().isEmpty());
    QVERIFY(!theme.absolutePath().isEmpty());
    QVERIFY(theme.author().isEmpty());
    QVERIFY(theme.authorEmail().isEmpty());
    QVERIFY(!theme.isValid());
}

void GrantleeThemeTest::shouldLoadTheme_data()
{
    QTest::addColumn<QString>("dirname");
    QTest::addColumn<QString>("filename");
    QTest::addColumn<bool>("isvalid");
    QTest::addColumn<QStringList>("displayExtraVariables");

    QTest::newRow("valid theme") << QStringLiteral("valid") << QStringLiteral("filename.testdesktop") << true << QStringList();
    QTest::newRow("not existing theme") << QStringLiteral("notvalid") << QStringLiteral("filename.testdesktop") << false << QStringList();
    QStringList extraVariables;
    extraVariables << QStringLiteral("foo") << QStringLiteral("bla");
    QTest::newRow("valid with extra variable") << QStringLiteral("valid-with-extravariables") << QStringLiteral("filename.testdesktop") << true
                                               << extraVariables;
}

void GrantleeThemeTest::shouldLoadTheme()
{
    QFETCH(QString, dirname);
    QFETCH(QString, filename);
    QFETCH(bool, isvalid);
    QFETCH(QStringList, displayExtraVariables);

    GrantleeTheme::Theme theme(QStringLiteral(GRANTLEETHEME_DATA_DIR "/themes/") + dirname, dirname, filename);
    QCOMPARE(theme.isValid(), isvalid);
    QCOMPARE(theme.displayExtraVariables(), displayExtraVariables);
    QCOMPARE(theme.dirName(), dirname);
}

bool GrantleeThemeTest::validateHtml(const QString &themePath, const QString &name, const QString &html)
{
    const QString outFileName = themePath + QStringLiteral("/%1.out").arg(name);
    const QString htmlFileName = themePath + QStringLiteral("/%1.out.html").arg(name);
    QFile outFile(outFileName);
    if (!outFile.open(QIODevice::WriteOnly)) {
        qDebug() << "impossible to open " << outFile.fileName();
        return false;
    }
    outFile.write(html.toUtf8());
    outFile.close();

    // validate xml and pretty-print for comparison
    // TODO add proper cmake check for xmllint and diff
    const QStringList args =
        {QStringLiteral("--format"), QStringLiteral("--encode"), QStringLiteral("UTF8"), QStringLiteral("--output"), htmlFileName, outFileName};

    const int result = QProcess::execute(QStringLiteral("xmllint"), args);
    return result == 0;
}

bool GrantleeThemeTest::compareHtml(const QString &generatedTheme, const QString &themePath, const QString &name)
{
    const QString htmlFileName = generatedTheme + QStringLiteral("/%1.out.html").arg(name);
    const QString referenceFileName = themePath + QStringLiteral("/%1_expected.html").arg(name);

    // get rid of system dependent or random paths
    {
        QFile f(htmlFileName);
        if (!f.open(QIODevice::ReadOnly)) {
            return false;
        }
        QString content = QString::fromUtf8(f.readAll());
        f.close();
        content.replace(QRegularExpression(QLatin1String("\"file:[^\"]*[/(?:%2F)]([^\"/(?:%2F)]*)\"")), QStringLiteral("\"file:\\1\""));
        if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            return false;
        }
        f.write(content.toUtf8());
        f.close();
    }

    // compare to reference file
    const QStringList args = {QStringLiteral("-u"), referenceFileName, htmlFileName};

    QProcess proc;
    proc.setProcessChannelMode(QProcess::ForwardedChannels);
    proc.start(QStringLiteral("diff"), args);
    if (!proc.waitForFinished()) {
        return false;
    }

    return proc.exitCode() == 0;
}

void GrantleeThemeTest::testRenderTemplate_data()
{
    QTest::addColumn<QString>("dirname");
    QTest::addColumn<bool>("isValid");
    QTest::addColumn<QString>("filename");
    QTest::addColumn<QString>("templateBasename");

    QTest::newRow("valid theme") << QStringLiteral("valid") << true << QStringLiteral("filename.testdesktop") << QStringLiteral("header");
    QTest::newRow("invalid theme") << QStringLiteral("invalid") << false << QStringLiteral("filename.testdesktop") << QString();
    QTest::newRow("color") << QStringLiteral("color") << true << QStringLiteral("color.testdesktop") << QStringLiteral("color");
}

void GrantleeThemeTest::testRenderTemplate()
{
    QFETCH(QString, dirname);
    QFETCH(bool, isValid);
    QFETCH(QString, filename);
    QFETCH(QString, templateBasename);

    const QString themePath = QStringLiteral(GRANTLEETHEME_DATA_DIR "/themes/") + dirname;
    const QString themeBinaryPath = QStringLiteral(GRANTLEETHEME_DATA_BUILD_DIR "/themes/") + dirname;
    QDir().mkpath(themeBinaryPath);

    QVariantHash data;
    data[QStringLiteral("icon")] = QStringLiteral("kde");
    data[QStringLiteral("name")] = QStringLiteral("KMail");
    data[QStringLiteral("subtitle")] = QStringLiteral("...just rocks!");
    data[QStringLiteral("title")] = QStringLiteral("Something's going on");
    data[QStringLiteral("subtext")] = QStringLiteral("Please wait, it will be over soon.");

    QPalette pal;
    pal.setColor(QPalette::Button, Qt::red);
    pal.setColor(QPalette::Active, QPalette::Base, Qt::red);
    pal.setColor(QPalette::Inactive, QPalette::Base, Qt::green);
    pal.setColor(QPalette::Disabled, QPalette::Base, Qt::blue);
    data[QStringLiteral("pal")] = QVariant::fromValue(pal);
    data[QStringLiteral("colorScheme")] = QVariant::fromValue(KColorScheme(QPalette::Normal, KColorScheme::View));

    GrantleeTheme::Theme theme(themePath, dirname, filename);
    QCOMPARE(theme.isValid(), isValid);

    if (isValid) {
        const QString result = theme.render(templateBasename + QStringLiteral(".html"), data);

        QVERIFY(validateHtml(themeBinaryPath, templateBasename, result));
        QVERIFY(compareHtml(themeBinaryPath, themePath, templateBasename));

        QFile::remove(themeBinaryPath + QLatin1Char('/') + templateBasename + QStringLiteral(".out"));
        QFile::remove(themeBinaryPath + QLatin1Char('/') + templateBasename + QStringLiteral(".out.html"));
    }
}

QTEST_GUILESS_MAIN(GrantleeThemeTest)
