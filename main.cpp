#include <iostream>
#include <algorithm>
#include <iomanip>
#include <QApplication>
#include <QTime>

#include "MainWindow.h"
#include "CellulaireAutomaat.h"
#include "Rules.h"
#include "Pathfinding.h"

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(2);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w(100,100);
    w.show();
    //CellulaireAutomaat A("../Maps/map001.txt");

    return QApplication::exec();
}
