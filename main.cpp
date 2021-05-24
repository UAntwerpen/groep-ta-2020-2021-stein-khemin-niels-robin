#include <iostream>
#include <algorithm>
#include <iomanip>
#include <QApplication>
#include <QTime>

#include "MainWindow.h"
#include "CellulaireAutomaat.h"
#include "Rules.h"
#include "Pathfinding.h"
#include "settingswindow.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w(100,100);
    w.show();
    w.showView();

    //CellulaireAutomaat A("../Maps/map001.txt");

    return QApplication::exec();
}
