//
// Created by stein on 25/05/2021.
//

#include "CitySimulation.h"
#include "lib/DesignByContract.h"

float CitySimulation::runSimulationGUI(int width, int height, const std::string &rules){
    REQUIRE(1 < width, "Width is too small(must be at least 2)!");
    REQUIRE(1 < height, "Height is too small(must be at least 2)!");
    int it = 0;
    CellulaireAutomaat automaat(width, height, rules, true);
    automaat.addMainStreet(0, width / 2);
    window = new MainWindow(width, height, &automaat);
    window->isEnabled();
    window->isVisible();
    window->show();
    float prev_score = automaat.getScore();
    while (!it || prev_score != automaat.getScore()){
        delay(500);
        if(!window->getPause()){
            prev_score = automaat.getScore();
            automaat.updateRules();
            window->addDay();
            window->updateAll();
            it++;
        }
    }
    std::cout << "test" << std::endl;
    while(true){
        delay(500);
        if(!window->getPause()){
            automaat.updateCells();
            window->addDay();
            window->updateAll();
            it++;
        }
    }
#pragma omp parallel sections
    {
#pragma omp section
    {
        while (window->isVisible()){
            QCoreApplication::processEvents(QEventLoop::AllEvents);
        }
    }
#pragma omp section
        {
            while (window->isVisible())
                automaat.updateCells();
        }
    }
    return automaat.getScore();
}

void CitySimulation::delay(int time) {
    QTime dieTime = QTime::currentTime().addMSecs(time);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

float CitySimulation::runSimulation(int width, int height, const std::string &rules) {
    REQUIRE(1 < width, "Width is too small(must be at least 2)!");
    REQUIRE(1 < height, "Height is too small(must be at least 2)!");
    int it = 0;
    CellulaireAutomaat automaat(width, height, rules, false);
    automaat.addMainStreet(0, width / 2);
    float prev_score = automaat.getScore();
    while (!it || prev_score != automaat.getScore()){
        prev_score = automaat.getScore();
        automaat.updateCells(true);
        automaat.updateRules();
        it++;
    }
    return automaat.getScore();
}

CitySimulation::CitySimulation(): window(nullptr) {}

CitySimulation::~CitySimulation() {
    delete window;
}
