// SPDX-FileCopyrightText: 2023 - 2025 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef OPTIONMANAGER_H
#define OPTIONMANAGER_H

#include "optiondatastruct.h"
#include "services/services_global.h"

#include <QObject>
#include <QVariant>

class OptionManagerPrivate;
class SERVICE_EXPORT OptionManager : public QObject
{
    Q_OBJECT
public:
    static OptionManager *getInstance();

    QString getMavenToolPath() const;
    QString getJdkToolPath() const;
    QString getGradleToolPath() const;
    QString getPythonToolPath() const;
    QString getNinjaToolPath() const;
    QString getJSToolPath() const;
    QString getToolPath(const QString &kit) const;
    QVariant getValue(const QString &category, const QString &key) const;
    void setValue(const QString &category, const QString &key, const QVariant& value);

private:
    explicit OptionManager(QObject *parent = nullptr);
    virtual ~OptionManager() override;

    OptionManagerPrivate *const d;
};

#endif // OPTIONMANAGER_H
