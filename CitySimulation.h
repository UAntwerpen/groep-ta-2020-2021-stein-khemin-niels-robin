

#ifndef TA_CITYSIMULATION_H
#define TA_CITYSIMULATION_H

#include <string>
#include "CellulaireAutomaat.h"

float runSimulation(const std::string& rules){
    int it = 0;
    int max = 10;
    float total_score = 0;
    CellulaireAutomaat automaat(10, 10, rules, false);
    automaat.addMainStreet(0, 5);
//    QApplication::exec();
    while (it < max){
        automaat.updateRules();
        automaat.updateCells();
        if (it > 5)
            total_score += automaat.getScore();
        automaat.draw();
        it++;
    }
    return total_score / (max + 1);
}

#endif //TA_CITYSIMULATION_H
