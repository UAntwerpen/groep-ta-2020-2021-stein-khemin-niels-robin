

#ifndef TA_CITYSIMULATION_H
#define TA_CITYSIMULATION_H

#include <string>
#include "CellulaireAutomaat.h"

float runSimulation(const string& rules){
    int it = 0;
    int max = 2000;
    CellulaireAutomaat automaat(50, 50, rules);
    automaat.changeCell(0, 25, new Cell)
    while (it < max){
        automaat.update();
        it++;
    }
}

#endif //TA_CITYSIMULATION_H
