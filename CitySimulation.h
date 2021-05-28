

#ifndef TA_CITYSIMULATION_H
#define TA_CITYSIMULATION_H
#include <QApplication>
#include <string>
#include <QTime>
#include "CellulaireAutomaat.h"
#include <iostream>

class CitySimulation {
public:
    void delay();
    float runSimulation(const std::string &rules);
};

float runSimulation(const std::string& rules){
    int it = 0;
    int max = 10;
    CellulaireAutomaat automaat(10, 10, rules, false);
    automaat.addMainStreet(0, 5);
    float prev_score = automaat.getScore();
//    QApplication::exec();
    while (!it || prev_score != automaat.getScore()){
        prev_score = automaat.getScore();
        automaat.updateRules();
        automaat.updateCells();
        it++;
    }
    return automaat.getScore();
}
#endif //TA_CITYSIMULATION_H
