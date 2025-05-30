// SPDX-FileCopyrightText: 2024 - 2025 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "notificationentity.h"

class NotificationEntityPrivate
{
public:
    QString name;
    QString message;
    QStringList actions;
    NotificationEntity::NotificationType type = NotificationEntity::Information;
    NotifyCallback callback;
};

NotificationEntity::NotificationEntity(NotificationType type, const QString &name, const QString &msg,
                                       const QStringList &actions, NotifyCallback cb, QObject *parent)
    : QObject(parent),
      d(new NotificationEntityPrivate)
{
    d->type = type;
    d->name = name;
    d->message = msg;
    d->actions = actions;
    d->callback = cb;
}

NotificationEntity::~NotificationEntity()
{
    delete d;
}

QString NotificationEntity::name() const
{
    return d->name;
}

void NotificationEntity::setName(const QString &name)
{
    d->name = name;
}

QString NotificationEntity::message() const
{
    return d->message;
}

void NotificationEntity::setMessage(const QString &msg)
{
    d->message = msg;
}

QStringList NotificationEntity::actions() const
{
    return d->actions;
}

void NotificationEntity::setActions(const QStringList &actions)
{
    d->actions = actions;
}

NotificationEntity::NotificationType NotificationEntity::type() const
{
    return d->type;
}

void NotificationEntity::setType(NotificationType type)
{
    d->type = type;
}

NotifyCallback NotificationEntity::callback() const
{
    return d->callback;
}

void NotificationEntity::setCallback(NotifyCallback cb)
{
    d->callback = cb;
}
