#ifndef CHANGEITEM_H
#define CHANGEITEM_H

#include <QWidget>
#include <QGroupBox>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "mainwidget.h"

class ChangeItem : public QWidget {
    Q_OBJECT
public:
    explicit ChangeItem(QString*,QWidget *parent = 0);

signals:
    void sendDeleteChange(QString);

public slots:
    void deleteChange();

private:
    QString* string;

    QHBoxLayout* layout;
    QLabel* label;
    QPushButton* button;
};

#endif // CHANGEITEM_H
