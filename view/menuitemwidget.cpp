#include "menuitemwidget.h"

MenuItemWidget::MenuItemWidget(Food* _food, QWidget *parent) : food(_food), QWidget(parent) {
    layout = new QHBoxLayout;
    foodName = new QLabel(food->getName());
    foodPrice = new QLabel(QString::number(food->getPrice(),'f',2));
    selectFood = new QPushButton("+");
    connect(selectFood,SIGNAL(clicked()),this,SLOT(getButton()));
    layout->addWidget(foodName,0,Qt::AlignTop);
    layout->addWidget(foodPrice,0,Qt::AlignTop);
    layout->addWidget(selectFood,0,Qt::AlignTop);
    setLayout(layout);
}

void MenuItemWidget::getButton() {
    emit valueButton(food);
}
