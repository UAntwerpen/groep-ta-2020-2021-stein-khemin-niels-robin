//
// Created by stein on 25/05/2021.
//

#include "CitySimulation.h"
#include "lib/DesignByContract.h"
#include "Vehicle.h"
#include "Citizen.h"
#include "Pathfinding.h"

#include <omp.h>

float CitySimulation::runSimulationGUI(int width, int height, const std::string &rules){
    REQUIRE(1 < width, "Width is too small(must be at least 2)!");
    REQUIRE(1 < height, "Height is too small(must be at least 2)!");
    int it = 0;
    CellulaireAutomaat automaat(width, height, rules, true);
    automaat.addMainStreet(0, width / 2);
    window = new MainWindow(width, height, &automaat);
    window->show();
    window->pauseSimulation();
    float prev_score = automaat.getScore();
    while ((!it || prev_score != automaat.getScore()) && window->isVisible()){
        delay(500);
        if(!window->getPause()){
            prev_score = automaat.getScore();
            automaat.updateRules();
            automaat.removeUnconnectedRoads();
            window->addDay();
            window->updateAll();
            it++;
        }
    }
    window->pauseSimulation();
    while(window->isVisible()){
        delay(500);
        if(!window->getPause()){
            automaat.updateCells();
            window->addDay();
            window->updateAll();
            it++;
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
    while ((!it || prev_score != automaat.getScore())){
        prev_score = automaat.getScore();
        automaat.updateCells(true);
        automaat.updateRules();
        automaat.removeUnconnectedRoads();
        it++;
    }
    return automaat.getScore();
}

void CitySimulation::runTransportSimulation(CellulaireAutomaat& map, int steps) {
    int carChance = 20;
    int pedestrianChance = 15;
    int pedestrianRange = 5;

    int currentStep = 0;

    MainWindow w(map.getWidth(), map.getHeight(), &map);
    w.show();

    int rowDim = map.getHeight();
    int colDim = map.getWidth();

    w.updateAll();
    while(currentStep < steps){
        for (int row = 0; row < rowDim; row++){
            for (int col = 0; col < colDim; col++){
                map(row, col)->update();
                int randRow = rand() % rowDim;
                int randCol = rand() % colDim;

                if (map(row, col)->getState() == EResidentialZone){
                    Vehicle* car = map(row, col)->getCar();

                    if (car->getStatus()) {
                        car->update(map);
                    } else if ((rand() % 100) <= carChance) {
                        // Voeg een passagier toe aan de auto als de auto leeg is.
                        if (car->getPeople().empty() && !map(row, col)->getPersons().empty()) {
                            int selectPerson = rand() % map(row, col)->getPersons().size();
                            if (!map(row, col)->getPersons()[selectPerson]->getStatus()){
                                car->addPerson(map(row, col)->getPersons()[selectPerson]);
                            }
                        }

                        Cell* goal = nullptr;
                        if (map(row, col) != car->getHome() && !car->getPeople().empty()) {
                            goal = car->getHome();
                        } else if (pair<int, int>(randRow, randCol) != car->getLocation()->getPos()&& !car->getPeople().empty()) {
                            goal = map(randRow, randCol);
                        }

                        car->setGoal(goal);
                        if (car->getGoal() != nullptr) {
                            auto* mask = new PFMask(map, car->getGoal(), true);
                            mask->generateMask();

                            car->setMask(mask);
                            car->calculateRoute();
                            car->update(map);
                        }
                    }
                    if(currentStep%4 ==0){
                        for (int i = 0; i < map(row, col)->getPersons().size(); i++) {
                            Citizen* person = map(row, col)->getPersons()[i];
                            pair<int, int> personPos = person->getLocation()->getPos();

                            if (person->getStatus()) {
                                person->update(map);
                            } else if (!person->getInCar() && (rand() % 100) <= pedestrianChance
                                       && abs(randRow - personPos.first) < pedestrianRange
                                       && abs(randCol - personPos.second) < pedestrianRange) {

                                Cell* goal = nullptr;
                                if (pair<int, int>(randRow, randCol) != person->getLocation()->getPos()) {
                                    goal = map(randRow, randCol);
                                }

                                person->setGoal(goal);
                                if (person->getGoal() != nullptr) {
                                    auto* mask = new PFMask(map, person->getGoal(), false);
                                    mask->generateMask();

                                    person->setMask(mask);
                                    person->calculateRoute();
                                    person->update(map);
                                }
                            }
                        }
                    }
                }
            }
        }
        w.updateVehicles();
        if(currentStep%4 ==0){
            w.updatePedestrians();
        }else{
            w.movePedestrians();
        }
        delay(200);

        for(int i = 0; i<7; i++){
            w.moveCars();
            w.movePedestrians();
            delay(200);
        }
        while(w.getPause()){
            delay(200);
        }
        currentStep += 1;
        if (currentStep % 10 == 0) {
            w.addDay();
        }
    }
}
CitySimulation::CitySimulation(): window(nullptr) {}

CitySimulation::~CitySimulation() {
    delete window;
}

