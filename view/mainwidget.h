#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include "actor.h"
#include "itemwidget.h"
#include "orderitemwidget.h"
#include "billwidget.h"

class MainWidget : public QWidget {
    Q_OBJECT

public:
    MainWidget(Actor* = new Actor(), QWidget *parent = 0);
    ~MainWidget();

public slots:
    void addItem();
    void payBill();
    void showNewItem();
    void removeItem(int);

signals:

private:
    Actor* actor;

    //GUI
    QGroupBox* hGroupBox;
    QGroupBox* showOrderGB;
    QVBoxLayout* showOrderLayout;
    QGroupBox* editOrderGB;
    QVBoxLayout* editOrderLayout;

    QScrollArea* scroll;

    GList<OrderItemWidget*> listItems;

    QPushButton* addItemButton;
    QPushButton* payBillButton;

    void createMainGroupBox();
    void createShowOrderGroupBox(QVBoxLayout*);

};

#endif // MAINWIDGET_H
