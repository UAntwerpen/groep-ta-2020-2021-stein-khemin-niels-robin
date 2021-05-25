

#ifndef TA_CITYSIMULATION_H
#define TA_CITYSIMULATION_H

#include <string>
#include "CellulaireAutomaat.h"

float runSimulation(const std::string& rules){
    int it = 0;
    int max = 200;
    CellulaireAutomaat automaat(10, 10, rules);
    automaat.changeCell(0, 5, new Road(0, 5, &automaat));
    automaat.draw();
    QApplication::exec();
//    while (it < max){
//        automaat.updateRules();
//        automaat.updateCells();
//        automaat.draw();
//        it++;
//    }
    return 0;
}

#endif //TA_CITYSIMULATION_H
