#include "loginwidget.h"
#include <QApplication>
#include<iostream>
#include"glist.h"

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWidget w;
    w.show();

    return a.exec();
}
