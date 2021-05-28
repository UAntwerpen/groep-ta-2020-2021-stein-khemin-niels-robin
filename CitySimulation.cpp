//
// Created by stein on 25/05/2021.
//

#include "CitySimulation.h"

float CitySimulation::runSimulationGUI(const std::string &rules){
    int it = 0;
    CellulaireAutomaat automaat(25, 25, rules, true);
    automaat.addMainStreet(0, 12);
    MainWindow w(25, 25, &automaat);
    w.show();
    float prev_score = automaat.getScore();
    while (!it || prev_score != automaat.getScore()){
        delay(1);
        if(!w.getPause()){
            prev_score = automaat.getScore();
            automaat.updateRules();
            automaat.updateCells();
            w.addDay();
            w.updateAll();
        it++;
        }
    }
    return automaat.getScore();
}

void CitySimulation::delay(double time) {
    QTime dieTime = QTime::currentTime().addSecs(std::round(time));
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

float CitySimulation::runSimulation(const std::string &rules) {
    int it = 0;
    CellulaireAutomaat automaat(10, 10, rules, false);
    automaat.addMainStreet(0, 5);
    float prev_score = automaat.getScore();
    while (!it || prev_score != automaat.getScore()){
        prev_score = automaat.getScore();
        automaat.updateRules();
        automaat.updateCells();
        it++;
    }
    return automaat.getScore();
}
