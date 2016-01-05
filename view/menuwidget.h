#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCloseEvent>
#include "mainwidget.h"
#include "menuitemwidget.h"

class MenuItemWidget;

class MenuWidget : public QWidget {
    Q_OBJECT
public:
    explicit MenuWidget(Actor*, QWidget *parent = 0);

signals:
    void food(Food*);
    void closeMenu(bool);

public slots:
    void selectFood(Food*);

private:
    Actor* actor;

    QGroupBox* vGroupBox;
    GList<MenuItemWidget*> itemList;

    void createMainGroupBox();
    void closeEvent(QCloseEvent*);
};

#endif // MENUWIDGET_H
