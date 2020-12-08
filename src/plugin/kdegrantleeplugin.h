/*
 * SPDX-FileCopyrightText: 2015 Daniel Vrátil <dvratil@redhat.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */

#ifndef KDEGRANTLEEPLUGIN_H
#define KDEGRANTLEEPLUGIN_H

#include <grantlee/taglibraryinterface.h>

class KDEGrantleePlugin : public QObject, public Grantlee::TagLibraryInterface
{
    Q_OBJECT
    Q_INTERFACES(Grantlee::TagLibraryInterface)
    Q_PLUGIN_METADATA(IID "org.kde.KDEGrantleePlugin")

public:
    explicit KDEGrantleePlugin(QObject *parent = nullptr);
    ~KDEGrantleePlugin() override;

    QHash<QString, Grantlee::Filter *> filters(const QString &name) override;
    QHash<QString, Grantlee::AbstractNodeFactory *> nodeFactories(const QString &name) override;
};

#endif // KDEGRANTLEEPLUGIN_H
