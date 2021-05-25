//
// Created by stein on 25/05/2021.
//

#include "CitySimulation.h"

float CitySimulation::runSimulation(const std::string &rules) {
    int it = 0;
    int max = 2000;
    CellulaireAutomaat automaat(10, 10, rules);
    automaat.changeCell(0, 5, new Road(0, 5, &automaat));
    while (it < max) {
        delay();
        automaat.updateRules();
        automaat.updateCells();
        automaat.draw();
        it++;
    }
    return 0;
}

void CitySimulation::delay() {
    QTime dieTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}