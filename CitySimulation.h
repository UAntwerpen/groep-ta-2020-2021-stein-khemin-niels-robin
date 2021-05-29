

#ifndef TA_CITYSIMULATION_H
#define TA_CITYSIMULATION_H
#include <QApplication>
#include <string>
#include <QTime>
#include "CellulaireAutomaat.h"
#include <iostream>

class CitySimulation {
public:
    void delay(double time);
    float runSimulationGUI(const std::string &rules);
    float runSimulation(const std::string &rules);
    void runTransportSimulation(CellulaireAutomaat& map, int steps);
};

#endif //TA_CITYSIMULATION_H
