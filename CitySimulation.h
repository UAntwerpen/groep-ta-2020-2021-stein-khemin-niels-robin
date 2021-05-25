//
// Created by stein on 25/05/2021.
//

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


#endif //TA_CITYSIMULATION_H
