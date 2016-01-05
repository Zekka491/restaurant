#ifndef MENUITEMWIDGET_H
#define MENUITEMWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <food.h>
#include "mainwidget.h"

class MenuItemWidget : public QWidget {
    Q_OBJECT
public:
    explicit MenuItemWidget(Food*,QWidget *parent = 0);

signals:
    void valueButton(Food*);

public slots:
    void getButton();

private:
    Food* food;

    QHBoxLayout* layout;
    QLabel* foodName;
    QLabel* foodPrice;
    QPushButton* selectFood;

};

#endif // MENUITEMWIDGET_H
