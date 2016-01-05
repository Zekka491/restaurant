#include "billwidget.h"

BillWidget::BillWidget(Order* _order, QWidget *parent) : order(_order), QWidget(parent) {
    layout = new QVBoxLayout;
    totalPrice = new QLabel(QString::number(order->getTotal(),'f',2));
    totalPrice->setFont(QFont(totalPrice->font().family(),30,1,false));
    buttonsGB = new QGroupBox;
    buttonsLayout = new QHBoxLayout;
    cancel = new QPushButton("Cancel");
    pay = new QPushButton("Pay");
    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(pay,SIGNAL(clicked()),this,SLOT(paid()));
    buttonsLayout->addWidget(cancel);
    buttonsLayout->addWidget(pay);
    buttonsGB->setLayout(buttonsLayout);
    layout->addWidget(new QLabel("TOTAL:"),20,Qt::AlignCenter);
    layout->addWidget(totalPrice,40,Qt::AlignCenter);
    layout->addWidget(buttonsGB,10);
    setLayout(layout);
}

void BillWidget::paid() {

}
