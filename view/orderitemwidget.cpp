#include "orderitemwidget.h"

OrderItemWidget::OrderItemWidget(OrderItem* _orderItem, QWidget *parent) : orderItem(_orderItem), QWidget(parent) {
    layout = new QVBoxLayout;

    createLabelGB();
    createListGB();
    createEditBarGB();

    QGroupBox* vBox = new QGroupBox;
    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(editBarGB,0,Qt::AlignTop);
    vLayout->addWidget(labelGB,0,Qt::AlignTop);
    if(orderItem->getChanges().size())
        vLayout->addWidget(listGB,0,Qt::AlignTop);
    vBox->setLayout(vLayout);

    layout->addWidget(vBox);
    setLayout(layout);
}

void OrderItemWidget::createEditBarGB(){
    editBarGB = new QGroupBox;
    editBarLayout = new QHBoxLayout;

    quantity = new QLabel(QString("Quantità: ").append(QString::number(orderItem->getQuantity())));
    totalPrice = new QLabel(QString("Prezzo totale: ").append(QString::number(orderItem->getQuantity()*(orderItem->getVarPrice()+orderItem->getFood()->getPrice()),'f',2)).append(QString(" €")));
    remove = new QPushButton("X");
    remove->setMaximumWidth(50);
    connect(remove,SIGNAL(clicked()),this,SLOT(removeItem()));
    editBarLayout->addWidget(quantity);
    editBarLayout->addWidget(totalPrice);
    editBarLayout->addWidget(remove);

    editBarGB->setLayout(editBarLayout);
}

void OrderItemWidget::createLabelGB() {
    labelGB = new QGroupBox;
    labelLayout = new QHBoxLayout;

    name = new QLabel(orderItem->getFood()->getName());
    price = new QLabel(QString("Prezzo unitario: ").append(QString::number(orderItem->getVarPrice()+orderItem->getFood()->getPrice(),'f',2)).append(QString(" €")));

    labelLayout->addWidget(name);
    labelLayout->addWidget(price);

    labelGB->setLayout(labelLayout);
}

void OrderItemWidget::createListGB() {
    listGB = new QGroupBox;
    listLayout = new QVBoxLayout;

    GList<QString>::iterator it;
    for(it = orderItem->getChanges().begin(); it != orderItem->getChanges().end(); it++) {
        changes.push_back(new QLabel(*it));
        (*changes.back())->setIndent(30);
        listLayout->addWidget(*changes.back());
    }

    listGB->setLayout(listLayout);
}

void OrderItemWidget::removeItem() {
    emit itemToRemove(orderItem->getId());
}

int OrderItemWidget::returnId() const {
    return orderItem->getId();
}
