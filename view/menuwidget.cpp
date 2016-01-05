#include "menuwidget.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>

MenuWidget::MenuWidget(Actor* _actor, QWidget *parent) : actor(_actor), QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QMenuBar* menuBar = new QMenuBar;

    //menu 'File'
    QMenu* fileMenu = menuBar->addMenu(tr("File"));
    QAction* newOrder = fileMenu->addAction(tr("New order"));
    fileMenu->addSeparator();
    QAction* closeAction = fileMenu->addAction(tr("Close"));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(close()));

    createMainGroupBox();

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(vGroupBox);
    setMinimumSize(500,500);
    setMaximumSize(500,500);
    resize(500,500);
    move(600,100);
    setLayout(mainLayout);
}

void MenuWidget::createMainGroupBox() {
    vGroupBox = new QGroupBox;
    QVBoxLayout* layout = new QVBoxLayout;
    GList<Food*>::iterator it;
    for(it = actor->getMenu().begin(); it != actor->getMenu().end(); it++) {
        itemList.push_back(new MenuItemWidget(*it));
        layout->addWidget(*(itemList.back()),0,Qt::AlignTop);
        connect((*itemList.back()),SIGNAL(valueButton(Food*)),this,SLOT(selectFood(Food*)));
    }
    vGroupBox->setLayout(layout);
}

void MenuWidget::selectFood(Food* _food) {
    emit food(_food);
    close();
}

void MenuWidget::closeEvent(QCloseEvent* event) {
    emit closeMenu(true);
    event->accept();
}
