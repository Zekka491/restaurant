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

    QString text() const;
signals:
    void valueButton(Food*);

public slots:
    void getButton();

private:
    Food* food;

    QVBoxLayout* mainLayout;
    QGroupBox* mainGB;
    QVBoxLayout* layout;
    QGroupBox* labelGB;
    QHBoxLayout* labelLayout;
    QGroupBox* plusGB;
    QHBoxLayout* plusLayout;

    QLabel* foodName;
    QLabel* foodPrice;
    QPushButton* selectFood;

    void writePlus();

};

#endif // MENUITEMWIDGET_H
