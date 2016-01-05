#ifndef ORDERITEMWIDGET_H
#define ORDERITEMWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include "orderitem.h"
#include "glist.h"

class OrderItemWidget : public QWidget {
    Q_OBJECT
public:
    explicit OrderItemWidget(OrderItem*, QWidget *parent = 0);

    int returnId() const;

signals:
    void itemToRemove(int);

public slots:
    void removeItem();

private:
    OrderItem* orderItem;

    QGroupBox* vGroupBox;
    QVBoxLayout* layout;

    QGroupBox* editBarGB;
    QHBoxLayout* editBarLayout;
    QLabel* quantity;
    QLabel* totalPrice;
    QPushButton* remove;

    QGroupBox* labelGB;
    QHBoxLayout* labelLayout;
    QLabel* name;
    QLabel* price;

    QGroupBox* listGB;
    QVBoxLayout* listLayout;
    GList<QLabel*> changes;

    void createEditBarGB();
    void createLabelGB();
    void createListGB();

};

#endif // ORDERITEMWIDGET_H
