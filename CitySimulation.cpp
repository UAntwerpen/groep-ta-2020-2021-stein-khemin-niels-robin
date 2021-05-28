//
// Created by stein on 25/05/2021.
//

#include "CitySimulation.h"

float CitySimulation::runSimulation(const std::string &rules) {
    int it = 0;
    int max = 2000;
    CellulaireAutomaat automaat(10, 10, rules);
    MainWindow w(10,10,&automaat);
    w.show();
    automaat.changeCell(0, 5, new Road(0, 5, &automaat));
    while (it < max) {
        delay(1);
        if(!w.getPause()){
            automaat.updateRules();
            automaat.updateCells();
            automaat.draw();
            w.addDay();
            w.updateAll();
            it++;
        }
    }
    return 0;
}

void CitySimulation::delay(double time) {
    QTime dieTime = QTime::currentTime().addSecs(time);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}