#ifndef BILLWIDGET_H
#define BILLWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "order.h"

class BillWidget : public QWidget {
    Q_OBJECT
public:
    explicit BillWidget(Order*, QWidget *parent = 0);

signals:
    void closeBill();

public slots:
    void paid();

private:
    Order* order;

    QVBoxLayout* layout;
    QLabel* totalPrice;

    QGroupBox* buttonsGB;
    QHBoxLayout* buttonsLayout;
    QPushButton* cancel;
    QPushButton* pay;
};

#endif // BILLWIDGET_H
