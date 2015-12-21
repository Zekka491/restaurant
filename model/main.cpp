//#include "loginwidget.h"
//#include <QApplication>
#include<iostream>
#include"seba.h"
#include"glist.h"

using namespace std;
int main()//int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    LoginWidget w;
    w.show();

    return a.exec();*/

    cout<<"crea lista"<<endl;
    GList<int> lista;
    cout<<"crea iteratore"<<endl;
    GList<int>::iterator it = lista.begin();
    cout<<"riempi lista"<<endl;
    for(int i=0;i<10;i++){
        lista.insert(it,i+1);
        it++;
    }
    cout<<"lunghezza lista = "<<lista.size()<<endl;
    cout<<"stampa dritta"<<endl;
    for(GList<int>::iterator it3 = lista.begin();it3 != lista.end(); it3++){
        cout << *it3 << " ";
    }
    cout<<endl<<"rovescia"<<endl;
    lista.reverse();

    cout<<"Stampa lista"<<endl;
    for(GList<int>::iterator it3 = lista.begin();it3 != lista.end(); it3++){
        cout << *it3 << " ";
    }

    cout<<endl<<"fine"<<endl;


}
