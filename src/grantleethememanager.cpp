/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "grantleethememanager.h"
#include "grantleetheme_p.h"

#include <KActionCollection>
#include <KActionMenu>
#include <KAuthorized>
#include <KConfigGroup>
#include <KDirWatch>
#include <KLocalizedString>
#include <KNewStuff3/KNS3/QtQuickDialogWrapper>
#include <KSharedConfig>
#include <KToggleAction>
#include <QAction>
#include <QIcon>
#include <QPointer>

#include <QActionGroup>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>

using namespace GrantleeTheme;
class Q_DECL_HIDDEN ThemeManager::Private
{
public:
    Private(const QString &type, const QString &desktopFileName, KActionCollection *ac, const QString &relativePath, ThemeManager *qq)
        : applicationType(type)
        , defaultDesktopFileName(desktopFileName)
        , actionCollection(ac)
        , q(qq)
    {
        watch = new KDirWatch(q);
        initThemesDirectories(relativePath);
        if (KAuthorized::authorize(QStringLiteral("ghns"))) {
            downloadThemesAction = new QAction(i18n("Download New Themes..."), q);
            downloadThemesAction->setIcon(QIcon::fromTheme(QStringLiteral("get-hot-new-stuff")));
            if (actionCollection) {
                actionCollection->addAction(QStringLiteral("download_header_themes"), downloadThemesAction);
            }
            separatorAction = new QAction(q);
            separatorAction->setSeparator(true);
            q->connect(downloadThemesAction, &QAction::triggered, q, [this]() {
                slotDownloadHeaderThemes();
            });
        }

        q->connect(watch, &KDirWatch::dirty, q, [this]() {
            directoryChanged();
        });
        updateThemesPath(true);

        // Migrate the old configuration format that only support mail and addressbook
        // theming to the new generic format
        KSharedConfig::Ptr config = KSharedConfig::openConfig();
        if (config->hasGroup(QStringLiteral("GrantleeTheme"))) {
            const KConfigGroup group = config->group(QStringLiteral("GrantleeTheme"));
            const QString mailTheme = group.readEntry(QStringLiteral("grantleeMailThemeName"));
            const QString addressbookTheme = group.readEntry(QStringLiteral("grantleeAddressBookThemeName"));

            config->group(QStringLiteral("mail")).writeEntry(QStringLiteral("themeName"), mailTheme);
            config->group(QStringLiteral("addressbook")).writeEntry(QStringLiteral("themeName"), addressbookTheme);

            config->deleteGroup(QStringLiteral("GrantleeTheme"));
        }
    }

    ~Private()
    {
        removeActions();
        themes.clear();
    }

    void slotDownloadHeaderThemes()
    {
        KNS3::QtQuickDialogWrapper(downloadConfigFileName).exec();
    }

    void directoryChanged()
    {
        updateThemesPath();
        updateActionList();
        Q_EMIT q->updateThemes();
    }

    void updateThemesPath(bool init = false)
    {
        if (!init) {
            if (!themesDirectories.isEmpty()) {
                for (const QString &directory : std::as_const(themesDirectories)) {
                    watch->removeDir(directory);
                }
            } else {
                return;
            }
        }

        // clear all previous theme information
        themes.clear();

        for (const QString &directory : std::as_const(themesDirectories)) {
            QDirIterator dirIt(directory, QStringList(), QDir::AllDirs | QDir::NoDotAndDotDot);
            QStringList alreadyLoadedThemeName;
            while (dirIt.hasNext()) {
                dirIt.next();
                const QString dirName = dirIt.fileName();
                GrantleeTheme::Theme theme = q->loadTheme(dirIt.filePath(), dirName, defaultDesktopFileName);
                if (theme.isValid()) {
                    QString themeName = theme.name();
                    if (alreadyLoadedThemeName.contains(themeName)) {
                        int i = 2;
                        const QString originalName(theme.name());
                        while (alreadyLoadedThemeName.contains(themeName)) {
                            themeName = originalName + QStringLiteral(" (%1)").arg(i);
                            ++i;
                        }
                        theme.d->name = themeName;
                    }
                    alreadyLoadedThemeName << themeName;
                    auto it = themes.find(dirName);
                    if (it != themes.end()) {
                        (*it).addThemePath(dirIt.filePath());
                    } else {
                        themes.insert(dirName, theme);
                    }
                }
            }
            watch->addDir(directory);
        }

        Q_EMIT q->themesChanged();
        watch->startScan();
    }

    void removeActions()
    {
        if (!actionGroup || !menu) {
            return;
        }
        for (KToggleAction *action : std::as_const(themesActionList)) {
            actionGroup->removeAction(action);
            menu->removeAction(action);
            if (actionCollection) {
                actionCollection->removeAction(action);
            }
        }
        if (separatorAction) {
            menu->removeAction(separatorAction);
            menu->removeAction(downloadThemesAction);
        }
        themesActionList.clear();
    }

    void updateActionList()
    {
        if (!actionGroup || !menu) {
            return;
        }
        QString themeActivated;

        QAction *selectedAction = actionGroup->checkedAction();
        if (selectedAction) {
            themeActivated = selectedAction->data().toString();
        }

        removeActions();

        bool themeActivatedFound = false;
        QMapIterator<QString, GrantleeTheme::Theme> i(themes);
        while (i.hasNext()) {
            i.next();
            GrantleeTheme::Theme theme = i.value();
            KToggleAction *act = new KToggleAction(theme.name(), q);
            act->setToolTip(theme.description());
            act->setData(theme.dirName());
            if (theme.dirName() == themeActivated) {
                act->setChecked(true);
                themeActivatedFound = true;
            }
            themesActionList.append(act);
            actionGroup->addAction(act);
            menu->addAction(act);
            q->connect(act, &KToggleAction::triggered, q, [this]() {
                slotThemeSelected();
            });
        }
        if (!themeActivatedFound) {
            if (!themesActionList.isEmpty() && !themeActivated.isEmpty()) {
                // Activate first item if we removed theme.
                KToggleAction *act = themesActionList.at(0);
                act->setChecked(true);
                selectTheme(act);
            }
        }
        if (separatorAction) {
            menu->addAction(separatorAction);
            menu->addAction(downloadThemesAction);
        }
    }

    void selectTheme(KToggleAction *act)
    {
        if (act) {
            KSharedConfig::Ptr config = KSharedConfig::openConfig();
            KConfigGroup group = config->group(applicationType);
            group.writeEntry(QStringLiteral("themeName"), act->data().toString());
            config->sync();
        }
    }

    void slotThemeSelected()
    {
        if (q->sender()) {
            auto act = qobject_cast<KToggleAction *>(q->sender());
            selectTheme(act);
            Q_EMIT q->grantleeThemeSelected();
        }
    }

    KToggleAction *actionForTheme()
    {
        const KSharedConfig::Ptr config = KSharedConfig::openConfig();
        const KConfigGroup group = config->group(applicationType);
        const QString themeName = group.readEntry(QStringLiteral("themeName"), QStringLiteral("default"));

        if (themeName.isEmpty()) {
            return nullptr;
        }
        for (KToggleAction *act : std::as_const(themesActionList)) {
            if (act->data().toString() == themeName) {
                return static_cast<KToggleAction *>(act);
            }
        }
        return nullptr;
    }

    void initThemesDirectories(const QString &themesRelativePath)
    {
        if (!themesRelativePath.isEmpty()) {
            themesDirectories = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, themesRelativePath, QStandardPaths::LocateDirectory);
            const QString localDirectory = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + themesRelativePath;
            themesDirectories.append(localDirectory);
        }
    }

    QString applicationType;
    QString defaultDesktopFileName;
    QString downloadConfigFileName;
    QStringList themesDirectories;
    QMap<QString, GrantleeTheme::Theme> themes;
    QVector<KToggleAction *> themesActionList;
    KDirWatch *watch = nullptr;
    QActionGroup *actionGroup = nullptr;
    KActionMenu *menu = nullptr;
    KActionCollection *const actionCollection;
    QAction *separatorAction = nullptr;

    QAction *downloadThemesAction = nullptr;
    ThemeManager *const q;
};

ThemeManager::ThemeManager(const QString &applicationType,
                           const QString &defaultDesktopFileName,
                           KActionCollection *actionCollection,
                           const QString &path,
                           QObject *parent)
    : QObject(parent)
    , d(new Private(applicationType, defaultDesktopFileName, actionCollection, path, this))
{
}

ThemeManager::~ThemeManager()
{
    delete d;
}

QMap<QString, GrantleeTheme::Theme> ThemeManager::themes() const
{
    return d->themes;
}

void ThemeManager::setActionGroup(QActionGroup *actionGroup)
{
    if (d->actionGroup != actionGroup) {
        d->removeActions();
        d->actionGroup = actionGroup;
        d->updateActionList();
    }
}

KToggleAction *ThemeManager::actionForTheme()
{
    return d->actionForTheme();
}

void ThemeManager::setThemeMenu(KActionMenu *menu)
{
    if (d->menu != menu) {
        d->menu = menu;
        d->updateActionList();
    }
}

QStringList ThemeManager::displayExtraVariables(const QString &themename) const
{
    QMapIterator<QString, GrantleeTheme::Theme> i(d->themes);
    while (i.hasNext()) {
        i.next();
        if (i.value().dirName() == themename) {
            return i.value().displayExtraVariables();
        }
    }
    return QStringList();
}

GrantleeTheme::Theme ThemeManager::theme(const QString &themeName)
{
    return d->themes.value(themeName);
}

void ThemeManager::setDownloadNewStuffConfigFile(const QString &configFileName)
{
    d->downloadConfigFileName = configFileName;
}

QString ThemeManager::pathFromThemes(const QString &themesRelativePath, const QString &themeName, const QString &defaultDesktopFileName)
{
    QStringList themesDirectories;
    if (!themesRelativePath.isEmpty()) {
        themesDirectories = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, themesRelativePath, QStandardPaths::LocateDirectory);
        if (themesDirectories.count() < 2) {
            // Make sure to add local directory
            const QString localDirectory = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + themesRelativePath;
            if (!themesDirectories.contains(localDirectory)) {
                themesDirectories.append(localDirectory);
            }
        }
        for (const QString &directory : std::as_const(themesDirectories)) {
            QDirIterator dirIt(directory, QStringList(), QDir::AllDirs | QDir::NoDotAndDotDot);
            while (dirIt.hasNext()) {
                dirIt.next();
                const QString dirName = dirIt.fileName();
                GrantleeTheme::Theme theme = loadTheme(dirIt.filePath(), dirName, defaultDesktopFileName);
                if (theme.isValid()) {
                    if (dirName == themeName) {
                        return theme.absolutePath();
                    }
                }
            }
        }
    }
    return QString();
}

GrantleeTheme::Theme ThemeManager::loadTheme(const QString &themePath, const QString &dirName, const QString &defaultDesktopFileName)
{
    const GrantleeTheme::Theme theme(themePath, dirName, defaultDesktopFileName);
    return theme;
}

QString ThemeManager::configuredThemeName() const
{
    return configuredThemeName(d->applicationType);
}

QString ThemeManager::configuredThemeName(const QString &themeType)
{
    const KSharedConfig::Ptr config = KSharedConfig::openConfig();
    const KConfigGroup grp = config->group(themeType);
    return grp.readEntry(QStringLiteral("themeName"));
}

#include "moc_grantleethememanager.cpp"
