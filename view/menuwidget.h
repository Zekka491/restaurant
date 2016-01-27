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
    explicit MenuWidget(Actor*, int, QWidget *parent = 0);

signals:
    void food(Food*);
    void closeMenu(bool);

public slots:
    void selectFood(Food*);
    void removeFood(Food*);
    void editFood(Food*);
    void updateMenu();

private:
    Actor* actor;
    int function;

    QGroupBox* vGroupBox;
    QVBoxLayout* layout;
    QScrollArea* scroll;
    GList<QGroupBox*> categoryGB;
    GList<QVBoxLayout*> categoryLayout;
    GList<MenuItemWidget*> itemList;

    void createMainGroupBox();
    void closeEvent(QCloseEvent*);
};

#endif // MENUWIDGET_H
