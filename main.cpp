#include <iostream>
#include <algorithm>
#include <iomanip>
#include <QApplication>

#include "MainWindow.h"
#include "CellulaireAutomaat.h"
#include "Rules.h"


int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w(100,100);
    w.show();
    return QApplication::exec();
}
