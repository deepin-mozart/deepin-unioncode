/**
 * C/C++ Debug Adaptor Protocol Server drived by google cppdap library
 *
 * Copyright (C) 2020 ~ 2022 Uniontech Software Technology Co., Ltd.
 *
 * Author:     huanyu<huanyub@uniontech.com>
 *
 * Maintainer: zhengyouge<zhengyouge@uniontech.com>
 *             xiaozaihu<xiaozaihu@uniontech.com>
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
#include "gdbproxy.h"
#include <QDebug>

GDBProxy *GDBProxy::instance(){
    static GDBProxy instance;
    return &instance;
}

GDBProxy::GDBProxy()
{

}


void GDBProxy::gdbProcessStarted()
{
    isGdbProcessStarted = true;
}

void GDBProxy::gdbProcessTerminated()
{
    isGDbProcessTerminated = true;
}

void GDBProxy::asyncRunning(/*const QString &thid*/)
{
    [=](const QString& thid) {
        qInfo() << "running, thread-id: " << thid;
    };
}

void GDBProxy::asyncStopped(/*const gdb::AsyncContext &ctx*/)
{
    [=](const gdb::AsyncContext& ctx){
        switch (ctx.reason) {
        case (gdb::AsyncContext::Reason::breakpointHhit): {
            qInfo() << "stopped reason: breakpoint Hit";
            break;
        }
        }
    };
}

void GDBProxy::breakpointModified(/*const gdb::Breakpoint &bp*/)
{
    qInfo() << "breakpoint modified";
}

void GDBProxy::librayLoaded()
{
    qInfo() << "Library Loaded";
}

void GDBProxy::libraryUnloaded()
{

}