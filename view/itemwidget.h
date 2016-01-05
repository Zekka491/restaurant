#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <mainwidget.h>
#include <QCloseEvent>
#include "menuwidget.h"
#include "addchange.h"
#include "changeitem.h"

class ChangeItem;

class ItemWidget : public QWidget {
    Q_OBJECT
public:
    explicit ItemWidget(Actor*,QWidget *parent = 0);

signals:
    void updateOrder();
    void closeItem();

public slots:
    void selectFood();
    void writeChange();
    void addChange(QString*);
    void saveItem();
    void removeChange(QString);
    void newFood(Food*);

private:
    Actor* actor;
    OrderItem* orderItem;

    //GUI
    QGroupBox* vGroupBox;
    QGroupBox* foodGB;
    QGroupBox* quantityGB;
    QGroupBox* changesGB;
    QGroupBox* buttonsGB;

    QLabel* foodLbl;
    QLabel* selectFoodLbl;
    QPushButton* foodBtn;

    QLabel* quantityLbl;
    QLineEdit* quantityTxt;

    QScrollArea* scroll;
    QGroupBox* labelListGB;
    QLabel* changesLbl;
    QPushButton* addChangeBtn;
    QGroupBox* listGB;
    QVBoxLayout* listLayout;
    GList<ChangeItem*> listLbl;

    QPushButton* submitBtn;
    QPushButton* cancelBtn;

    void createMainGroupBox();
    void printChanges();
    void closeEvent(QCloseEvent*);

};

#endif // ITEMWIDGET_H
