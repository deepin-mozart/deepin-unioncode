// SPDX-FileCopyrightText: 2023 - 2025 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <qglobal.h>

QT_BEGIN_NAMESPACE
class QString;
class QWidget;
QT_END_NAMESPACE

namespace Internal {

QWidget *warning(const QString &title, const QString &desciption);
QWidget *information(const QString &title, const QString &desciption);
QWidget *critical(const QString &title, const QString &desciption);

}

#endif // MESSAGEBOX_H
