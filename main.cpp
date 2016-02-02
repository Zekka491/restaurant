#include "mainwidget.h"
#include <QApplication>
#include<iostream>
#include"glist.h"
#include"dish.h"
#include"beverage.h"
#include"actor.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWidget w;

    w.show();

    return a.exec();
}
