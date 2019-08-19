/*
  Copyright (c) 2013-2019 Montel Laurent <montel@kde.org>

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
