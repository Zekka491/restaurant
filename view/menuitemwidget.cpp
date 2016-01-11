#include "menuitemwidget.h"

MenuItemWidget::MenuItemWidget(Food* _food, QWidget *parent) : food(_food), QWidget(parent) {
    mainLayout = new QVBoxLayout;
    mainGB = new QGroupBox;
    layout = new QVBoxLayout;

    labelGB = new QGroupBox;
    labelLayout = new QHBoxLayout;
    foodName = new QLabel(food->getName());
    foodPrice = new QLabel(QString::number(food->getPrice(),'f',2));
    selectFood = new QPushButton("+");
    connect(selectFood,SIGNAL(clicked()),this,SLOT(getButton()));
    labelLayout->addWidget(foodName,0,Qt::AlignTop);
    labelLayout->addWidget(foodPrice,0,Qt::AlignTop);
    labelLayout->addWidget(selectFood,0,Qt::AlignTop);
    labelGB->setLayout(labelLayout);

    writePlus();

    layout->addWidget(labelGB);
    layout->addWidget(plusGB);
    mainGB->setLayout(layout);
    mainLayout->addWidget(mainGB);
    setLayout(mainLayout);
}

void MenuItemWidget::writePlus() {
    plusGB = new QGroupBox;
    plusLayout = new QHBoxLayout;
    if(dynamic_cast<Dish*>(food)) {
        Dish* dish = static_cast<Dish*>(food);
        GList<QString>::iterator it;
        QString string;
        for(it = dish->getIngredients().begin(); it != dish->getIngredients().end(); it++) {
            string.append(*it).append(", ");
        }
        string.remove(string.size()-2,2);
        plusLayout->addWidget(new QLabel(string));
    } else {
        Beverage* beverage = static_cast<Beverage*>(food);
        QLabel* label = new QLabel("Capacity:");
        QLabel* capacity = new QLabel(QString::number(beverage->getCapacity(),'f',2));
        capacity->setMaximumWidth(50);
        plusLayout->addWidget(label,10);
        plusLayout->addWidget(capacity,80,Qt::AlignLeft);
    }
    plusGB->setLayout(plusLayout);
}

void MenuItemWidget::getButton() {
    emit valueButton(food);
}

QString MenuItemWidget::text() const {
    return foodName->text();
}
