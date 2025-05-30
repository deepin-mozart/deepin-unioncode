// SPDX-FileCopyrightText: 2023 - 2025 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "messagedata.h"

#include <QDebug>

MessageData::MessageData()
{
}

MessageData::MessageData(const QString &id, Type type)
    : msgId(id),
      msgType(type)
{
}

void MessageData::updateData(const QString &data)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QStringList lines = data.split("\n", Qt::SkipEmptyParts);
 #else
    QStringList lines = data.split("\n", QString::SkipEmptyParts);
 #endif
    if (lines.length() < msgDataLines.length())
        return;

    msgData = data;
    msgDataLines = lines;
    //    qInfo() << "update msg line" << msgDataLines;
}

void MessageData::appendData(const QStringList &data)
{
    msgDataLines.append(data);
    msgData.append(data.join("\n"));
}

QString MessageData::messageID() const
{
    return msgId;
}

MessageData::Type MessageData::messageType() const
{
    return msgType;
}

QString MessageData::messageData() const
{
    return msgData;
}

QStringList MessageData::messageLines() const
{
    return msgDataLines;
}
