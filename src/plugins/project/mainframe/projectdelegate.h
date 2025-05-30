// SPDX-FileCopyrightText: 2023 - 2025 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef PROJECTDELEGATE_H
#define PROJECTDELEGATE_H

#include "base/baseitemdelegate.h"

class ProjectDelegatePrivate;
class ProjectDelegate : public BaseItemDelegate
{
    Q_OBJECT
    ProjectDelegatePrivate *const d;
public:
    explicit ProjectDelegate(QAbstractItemView *parent = nullptr);
    ~ProjectDelegate() override;
    void setActiveProject(const QModelIndex &root);
    const QModelIndex &getActiveProject() const;
    void hideSpinner();

protected:
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
};

#endif // PROJECTDELEGATE_H
