

#ifndef TA_CITYSIMULATION_H
#define TA_CITYSIMULATION_H

#include <QApplication>
#include <string>
#include <QTime>
#include "CellulaireAutomaat.h"
void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


float runSimulation(const std::string& rules){
    int it = 0;
    int max = 2000;
    CellulaireAutomaat automaat(10, 10, rules);
    automaat.changeCell(0, 5, new Road(0, 5, &automaat));
    while (it < max){
        delay();
        automaat.updateRules();
        automaat.updateCells();
        automaat.draw();
        it++;
    }
    return 0;
}

#endif //TA_CITYSIMULATION_H
