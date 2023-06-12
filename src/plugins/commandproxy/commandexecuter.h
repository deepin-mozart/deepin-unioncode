/*
 * Copyright (C) 2023 Uniontech Software Technology Co., Ltd.
 *
 * Author:     hongjinchuan<hongjinchuan@uniontech.com>
 *
 * Maintainer: hongjinchuan<hongjinchuan@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef COMMANDEXECUTER_H
#define COMMANDEXECUTER_H

#include <framework/framework.h>
#include <QObject>

class CommandExecuter: QObject
{
    Q_OBJECT
public:
    static CommandExecuter &instance();
    void buildProject();

private:
    explicit CommandExecuter(QObject *parent = nullptr);
    QStringList exeFileName(QDir dir);

};

#endif   // COMMANDEXECUTER_H