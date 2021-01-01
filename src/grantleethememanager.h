/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef GRANTLEETHEMEMANAGER_H
#define GRANTLEETHEMEMANAGER_H

#include "grantleetheme.h"
#include "grantleetheme_export.h"
#include <QObject>
#include <QMap>
class QActionGroup;
class KActionCollection;
class KToggleAction;
class KActionMenu;

namespace GrantleeTheme {
/**
 * @brief The ThemeManager class
 * @author Laurent montel <montel@kde.org>
 */
class GRANTLEETHEME_EXPORT ThemeManager : public QObject
{
    Q_OBJECT
public:
    explicit ThemeManager(const QString &themeType, const QString &defaultDesktopFileName, KActionCollection *actionCollection = nullptr, const QString &path = QString(), QObject *parent = nullptr);
    ~ThemeManager();

    Q_REQUIRED_RESULT QMap<QString, GrantleeTheme::Theme> themes() const;

    void setActionGroup(QActionGroup *actionGroup);

    Q_REQUIRED_RESULT KToggleAction *actionForTheme();

    void setThemeMenu(KActionMenu *menu);

    Q_REQUIRED_RESULT QStringList displayExtraVariables(const QString &themename) const;

    Q_REQUIRED_RESULT GrantleeTheme::Theme theme(const QString &themeName);

    void setDownloadNewStuffConfigFile(const QString &configFileName);

    Q_REQUIRED_RESULT QString configuredThemeName() const;
    Q_REQUIRED_RESULT static QString configuredThemeName(const QString &themeType);

    Q_REQUIRED_RESULT static QString pathFromThemes(const QString &path, const QString &themeName, const QString &defaultDesktopFilename);
    Q_REQUIRED_RESULT static GrantleeTheme::Theme loadTheme(const QString &themePath, const QString &dirName, const QString &defaultDesktopFilename);

Q_SIGNALS:
    void themesChanged();
    void grantleeThemeSelected();
    void updateThemes();

private:
    class Private;
    Private *const d;
    Q_PRIVATE_SLOT(d, void directoryChanged())
};
}
#endif // GRANTLEETHEMEMANAGER_H
