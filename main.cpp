#include <iostream>
#include <algorithm>
#include <iomanip>
#include <QApplication>

#include "MainWindow.h"
#include "CellulaireAutomaat.h"
#include "Rules.h"
#include "Pathfinding.h"


int main(int argc, char *argv[]){
//    QApplication a(argc, argv);
//    MainWindow w(100,100);
//    w.show();
    CellulaireAutomaat A("../Maps/map001.txt");

    return /*QApplication::exec()*/0;
}
