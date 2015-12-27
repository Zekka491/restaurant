//#include "loginwidget.h"
//#include <QApplication>
#include<iostream>
#include"glist.h"
#include"dish.h"
#include"beverage.h"
#include"actor.h"

using namespace std;
int main()//int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    LoginWidget w;
    w.show();

    return a.exec();*/



    /*Food* viennese = new Dish("Viennese",7.50,"Pizza");
    Dish* newViennese;
    if(dynamic_cast<Dish*>(viennese)) {
        newViennese = static_cast<Dish*>(viennese);
        newViennese->addIngredient("mozzarella");
        newViennese->addIngredient("pomodoro");
        newViennese->addIngredient("wurstel");
    }
    cout << *newViennese;

    Food* margherita = new Dish("Margherita",5.50,"Pizza");
    //margherita->addIngredient("mozzarella");
    //margherita->addIngredient("pomodoro");
    //margherita->
    cout << *margherita;


    Food* cocacola = new Beverage("Coca-Cola",3,"Bibita",0.33);
    cout << *cocacola;


    if(*newViennese>*margherita)
        cout<<"confronto vero"<<endl;
    else
        cout<<"confronto falso"<<endl;*/

    Actor* patroMenu = new Actor();
    patroMenu->loadMenu();
    GList<Food*> menu = patroMenu->getMenu();
    GList<Food*>::iterator it;
    for(it=menu.begin(); it!=menu.end(); it++) {
        cout<<"piatto : ";
        if(dynamic_cast<Dish*>(*it)) {
            Dish* dish = static_cast<Dish*>(*it);
            cout<<*dish<<endl;
        } else {
            Beverage* beverage = static_cast<Beverage*>(*it);
            cout<<*beverage<<endl;
        }
        //carica i piatti e le bavande invertite
    }

    //patroMenu->saveMenu();

}
