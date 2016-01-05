#include "changeitem.h"

ChangeItem::ChangeItem(QString* _string, QWidget *parent) : string(_string), QWidget(parent) {
    layout = new QHBoxLayout;
    label = new QLabel(*string);
    button = new QPushButton("X");
    connect(button,SIGNAL(clicked()),this,SLOT(deleteChange()));
    layout->addWidget(label,90,Qt::AlignTop);
    layout->addWidget(button,10,Qt::AlignTop);
    setLayout(layout);
}

void ChangeItem::deleteChange() {
    emit sendDeleteChange(label->text());
}

