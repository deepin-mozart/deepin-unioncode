// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include <framework/framework.h>

#include <QObject>

/**
 * @brief The EventReceiverDemo class
 * It will auto registered, and receive subscribed topics events.
 */
class CodeGeeXReceiver : public dpf::EventHandler, dpf::AutoEventHandlerRegister<CodeGeeXReceiver>
{
    friend class dpf::AutoEventHandlerRegister<CodeGeeXReceiver>;

public:
    explicit CodeGeeXReceiver(QObject *parent = nullptr);
    static Type type();
    static QStringList topics();

private:
    virtual void eventProcess(const dpf::Event &event) override;

    void processContextMenuEvent(const dpf::Event &event);
    void processSelectionChangedEvent(const dpf::Event &event);
    void processInlineWidgetClosedEvent(const dpf::Event &event);
    void processActionInvokedEvent(const dpf::Event &event);
    void processOpenProjectEvent(const dpf::Event &event);
    void processSwitchToWidget(const dpf::Event &event);
    void processLLMChanged();

private:
    QHash<QString, std::function<void(const dpf::Event &)>> eventHandleMap;
};

class CodeGeeXCallProxy : public QObject
{
    Q_OBJECT
    CodeGeeXCallProxy(const CodeGeeXCallProxy &) = delete;
    CodeGeeXCallProxy();
public:
    static CodeGeeXCallProxy *instance();

signals:
    void LLMsChanged();
    void selectionChanged();
    void switchToWidget(const QString &name);
};

#endif   // EVENTRECEIVER_H
