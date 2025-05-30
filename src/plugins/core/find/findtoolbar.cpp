// SPDX-FileCopyrightText: 2024 - 2025 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "findtoolbar.h"
#include "placeholdermanager.h"

#include "common/actionmanager/actionmanager.h"
#include "common/actionmanager/actioncontainer.h"
#include "common/find/abstractdocumentfind.h"
#include "base/abstractaction.h"
#include "services/window/windowservice.h"

#include <DLineEdit>
#include <DIconButton>
#include <DPushButton>

#include <QAction>
#include <QHBoxLayout>
#include <QApplication>

using namespace dpfservice;
DWIDGET_USE_NAMESPACE

constexpr char M_FIND[] = "Find.FindMenu";
constexpr char G_FIND_CURRENTDOCUMENT[] = "Find.FindMenu.CurrentDocument";
constexpr char G_FIND_ACTIONS[]   = "Find.FindMenu.Actions";

class FindToolBarPrivate
{
public:
    explicit FindToolBarPrivate(FindToolBar *qq);

    void initUI();
    void initConnection();
    void initActions();
    void updateUI();

    FindToolBar *q;
    AbstractDocumentFind *docFind { nullptr };
    DLineEdit *findEdit { nullptr };
    DLineEdit *replaceEdit { nullptr };
    DIconButton *findNextButton { nullptr };
    DIconButton *findPrevButton { nullptr };
    DPushButton *replaceButton { nullptr };
    DPushButton *replaceAllButton { nullptr };
    DPushButton *replaceFindButton { nullptr };
    DIconButton *closeButton { nullptr };
};

FindToolBarPrivate::FindToolBarPrivate(FindToolBar *qq)
    : q(qq)
{
}

void FindToolBarPrivate::initUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(q);
    mainLayout->setContentsMargins(10, 6, 10, 6);

    findEdit = new DLineEdit(q);
    findEdit->setPlaceholderText(FindToolBar::tr("Find"));
    findEdit->setMinimumWidth(100);

    replaceEdit = new DLineEdit(q);
    replaceEdit->setPlaceholderText(FindToolBar::tr("Replace"));
    replaceEdit->setMinimumWidth(100);

    findPrevButton = new DIconButton(q);
    findPrevButton->setIcon(QIcon::fromTheme("go-up"));

    findNextButton = new DIconButton(q);
    findNextButton->setIcon(QIcon::fromTheme("go-down"));

    replaceButton = new DPushButton(FindToolBar::tr("Replace"), q);
    replaceAllButton = new DPushButton(FindToolBar::tr("Replace All"), q);
    replaceFindButton = new DPushButton(FindToolBar::tr("Replace && Find"), q);

    closeButton = new DIconButton(DStyle::SP_CloseButton, q);
    closeButton->setIconSize(QSize(30, 30));
    closeButton->setFixedSize(30, 30);
    closeButton->setEnabledCircle(true);
    closeButton->setFlat(true);

    mainLayout->addWidget(findEdit);
    mainLayout->addWidget(replaceEdit);
    mainLayout->addWidget(findPrevButton);
    mainLayout->addWidget(findNextButton);
    mainLayout->addWidget(replaceButton);
    mainLayout->addWidget(replaceAllButton);
    mainLayout->addWidget(replaceFindButton);
    mainLayout->addWidget(closeButton);

    q->setFocusProxy(findEdit);
}

void FindToolBarPrivate::initConnection()
{
    q->connect(closeButton, &DIconButton::clicked, q, &FindToolBar::hideAndResetFocus);
    q->connect(findEdit, &DLineEdit::textChanged, q, &FindToolBar::findTextChanged);
    q->connect(findEdit, &DLineEdit::returnPressed, q, &FindToolBar::findNext);
    q->connect(replaceEdit, &DLineEdit::returnPressed, q, &FindToolBar::replaceFind);
    q->connect(findNextButton, &DIconButton::clicked, q, &FindToolBar::findNext);
    q->connect(findPrevButton, &DIconButton::clicked, q, &FindToolBar::findPrevious);
    q->connect(replaceButton, &DPushButton::clicked, q, &FindToolBar::replace);
    q->connect(replaceAllButton, &DPushButton::clicked, q, &FindToolBar::replaceAll);
    q->connect(replaceFindButton, &DPushButton::clicked, q, &FindToolBar::replaceFind);
}

void FindToolBarPrivate::initActions()
{
    auto mEdit = ActionManager::instance()->actionContainer(M_EDIT);
    auto mFind = ActionManager::instance()->createContainer(M_FIND);
    mFind->menu()->setTitle("&Find/Replace");
    mFind->appendGroup(G_FIND_CURRENTDOCUMENT);
    mFind->appendGroup(G_FIND_ACTIONS);
    mFind->addSeparator(G_FIND_ACTIONS);
    mEdit->addMenu(mFind, G_EDIT_FIND);

    QAction *findReplaceAction = new QAction(FindToolBar::tr("Find/Replace"), q);
    auto cmd = ActionManager::instance()->registerAction(findReplaceAction, "Find.findInDocument");
    cmd->setDefaultKeySequence(Qt::CTRL | Qt::Key_F);
    mFind->addAction(cmd, G_FIND_CURRENTDOCUMENT);
    q->connect(findReplaceAction, &QAction::triggered, q, [this] { q->openFindToolBar(); });

    QAction *findNextAction = new QAction(FindToolBar::tr("Find Next"), q);
    cmd = ActionManager::instance()->registerAction(findNextAction, "Find.findNext");
    cmd->setDefaultKeySequence(Qt::Key_F3);
    mFind->addAction(cmd, G_FIND_ACTIONS);
    q->connect(findNextAction, &QAction::triggered, q, [this] {
        if (q->isVisible())
            q->findNext();
    });

    QAction *findPreviousAction = new QAction(FindToolBar::tr("Find Previous"), q);
    cmd = ActionManager::instance()->registerAction(findPreviousAction, "Find.findPrevious");
    cmd->setDefaultKeySequence(Qt::SHIFT | Qt::Key_F3);
    mFind->addAction(cmd, G_FIND_ACTIONS);
    q->connect(findPreviousAction, &QAction::triggered, q, [this] {
        if (q->isVisible())
            q->findPrevious();
    });
}

void FindToolBarPrivate::updateUI()
{
    if (!docFind)
        return;

    bool canReplace = docFind->supportsReplace();
    replaceEdit->setVisible(canReplace);
    replaceButton->setVisible(canReplace);
    replaceFindButton->setVisible(canReplace);
    replaceAllButton->setVisible(canReplace);
}

FindToolBar::FindToolBar(QWidget *parent)
    : DFloatingWidget(parent),
      d(new FindToolBarPrivate(this))
{
    d->initUI();
    d->initConnection();
    d->initActions();
}

FindToolBar::~FindToolBar()
{
    delete d;
}

void FindToolBar::openFindToolBar()
{
    FindToolBarPlaceHolder *holder = findToolBarPlaceHolder();
    if (!holder)
        return;

    d->docFind = PlaceHolderManager::instance()->findDocumentFind(holder);
    if (!d->docFind)
        return;

    FindToolBarPlaceHolder *previousHolder = PlaceHolderManager::instance()->getCurrentHolder();
    if (previousHolder != holder) {
        if (previousHolder)
            previousHolder->setWidget(nullptr);
        holder->setWidget(this);
        PlaceHolderManager::instance()->setCurrentHolder(holder);
    }

    d->updateUI();
    holder->setVisible(true);
    setVisible(true);

    setFindText(d->docFind->findString());
    setFocus();
}

void FindToolBar::findNext()
{
    if (d->docFind)
        d->docFind->findNext(d->findEdit->text());
}

void FindToolBar::findPrevious()
{
    if (d->docFind)
        d->docFind->findPrevious(d->findEdit->text());
}

void FindToolBar::replace()
{
    if (d->docFind)
        d->docFind->replace(d->findEdit->text(), d->replaceEdit->text());
}

void FindToolBar::replaceFind()
{
    if (d->docFind)
        d->docFind->replaceFind(d->findEdit->text(), d->replaceEdit->text());
}

void FindToolBar::replaceAll()
{
    if (d->docFind)
        d->docFind->replaceAll(d->findEdit->text(), d->replaceEdit->text());
}

void FindToolBar::findTextChanged()
{
    if (d->docFind)
        d->docFind->findStringChanged();
}

void FindToolBar::hideAndResetFocus()
{
    auto holder = PlaceHolderManager::instance()->getCurrentHolder();
    if (holder)
        holder->setFocus();
    hide();
}

void FindToolBar::showEvent(QShowEvent *event)
{
    findTextChanged();
    DFloatingWidget::showEvent(event);
}

void FindToolBar::setFindText(const QString &text)
{
    if (!text.isEmpty())
        d->findEdit->setText(text);
    d->findEdit->lineEdit()->selectAll();
}

FindToolBarPlaceHolder *FindToolBar::findToolBarPlaceHolder()
{
    auto infos = PlaceHolderManager::instance()->allHolderInfo();
    QWidget *candidate = QApplication::focusWidget();
    while (candidate) {
        for (FindToolBarPlaceHolder *ph : infos.keys()) {
            if (ph->getOwner() == candidate)
                return ph;
        }
        candidate = candidate->parentWidget();
    }
    return nullptr;
}
