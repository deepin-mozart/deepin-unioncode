// SPDX-FileCopyrightText: 2024 - 2025 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "aptinstaller.h"

#include "common/util/eventdefinitions.h"
#include "services/terminal/terminalservice.h"
#include "services/window/windowelement.h"

#include <QProcess>

using namespace dpfservice;

APTInstaller::APTInstaller(QObject *parent)
    : AbstractInstaller(parent)
{
}

QString APTInstaller::description()
{
    return tr("Install packages by apt");
}

bool APTInstaller::checkInstalled(const QString &package)
{
    QProcess process;
    QString command = "dpkg-query -W -f='${Status}' " + package;

    process.start(command);
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    return output.contains("install ok installed");
}

void APTInstaller::install(const InstallInfo &info)
{
    if (!termSrv)
        termSrv = dpfGetService(TerminalService);

    QStringList args;
    args << "install"
         << info.packageList;

    uiController.switchContext(TERMINAL_TAB_TEXT);
    termSrv->executeCommand(info.plugin.isEmpty() ? "APTInstall" : info.plugin, "sudo apt", args, "", QStringList());
}
