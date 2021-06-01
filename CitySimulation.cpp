//
// Created by stein on 25/05/2021.
//

#include "CitySimulation.h"
#include "lib/DesignByContract.h"
#include "Vehicle.h"
#include "Citizen.h"
#include "Pathfinding.h"

float CitySimulation::runSimulationGUI(int width, int height, const std::string &rules){
    REQUIRE(1 < width, "Width is too small(must be at least 2)!");
    REQUIRE(1 < height, "Height is too small(must be at least 2)!");
    int carChance = 20;
    int pedestrianChance = 15;
    int pedestrianRange = 5;

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
        int transparent = 120;
        carChance = 20;
        delay(500);
        int dayLength = window->getDayLengthValue();
        for(int currentStep = 0; currentStep < dayLength; currentStep++){
            if(currentStep == (int) dayLength/2){
                carChance = 5;
                transparent = 0;
            }
            for (int row = 0; row < height; row++){
                for (int col = 0; col < width; col++){
                    int randRow = rand() % height;
                    int randCol = rand() % width;

                    if (automaat(row, col)->getState() == EResidentialZone){
                        Vehicle* car = automaat(row, col)->getCar();

                        if (car->getStatus()) {
                            car->update(automaat);
                        } else if ((rand() % 100) <= carChance) {
                            // Voeg een passagier toe aan de auto als de auto leeg is.
                            if (car->getPeople().empty() && !automaat(row, col)->getPersons().empty()) {
                                int selectPerson = rand() % automaat(row, col)->getPersons().size();
                                if (!automaat(row, col)->getPersons()[selectPerson]->getStatus()){
                                    car->addPerson(automaat(row, col)->getPersons()[selectPerson]);
                                }
                            }

                            pair<int, int> goal = std::make_pair(-1,-1);
                            if (automaat(row, col)->getPos() != car->getHome() && !car->getPeople().empty()) {
                                goal = car->getHome();
                            } else if (pair<int, int>(randRow, randCol) != car->getLocation() && !car->getPeople().empty()) {
                                goal = automaat(randRow, randCol)->getPos();
                            }

                            car->setGoal(goal);
                            if (car->getGoal() != std::make_pair(-1,-1)) {
                                auto mask = new PFMask(automaat, car->getGoal(), true);
                                mask->generateMask();

                                car->setMask(mask);
                                car->calculateRoute();
                                car->update(automaat);
                            }
                        }
                        if(currentStep%4 ==0){
                            for (int i = 0; i < (int) automaat(row, col)->getPersons().size(); i++) {
                                Citizen* person = automaat(row, col)->getPersons()[i];
                                pair<int, int> personPos = person->getLocation();

                                if (person->getStatus()) {
                                    person->update(automaat);
                                } else if (!person->getInCar() && (rand() % 100) <= pedestrianChance
                                           && abs(randRow - personPos.first) < pedestrianRange
                                           && abs(randCol - personPos.second) < pedestrianRange) {

                                    pair<int, int> goal = std::make_pair(-1,-1);
                                    if (pair<int, int>(randRow, randCol) != person->getLocation()) {
                                        goal = automaat(randRow, randCol)->getPos();
                                    }

                                    person->setGoal(goal);
                                    if (person->getGoal() != std::make_pair(-1,-1)) {
                                        auto mask = new PFMask(automaat, person->getGoal(), false);
                                        mask->generateMask();

                                        person->setMask(mask);
                                        person->calculateRoute();
                                        person->update(automaat);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            window->updateVehicles();
            if(currentStep%4 ==0){
                window->updatePedestrians();
            }else{
                window->movePedestrians();
            }
            delay(100);
            for(int i = 0; i<7; i++){
                while(window->getPause()){
                    delay(100);
                }
                if(currentStep == dayLength/2){
                    transparent += 15;
                    window->setDayOrNight(transparent);
                }
                if(currentStep == 0){
                    transparent -= 15;
                    window->setDayOrNight(transparent);
                }
                window->moveVehicles();
                window->movePedestrians();
                delay(100);
            }
        }

        automaat.updateCells();
        window->updateAll();
        window->addDay();
        it++;
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

CitySimulation::CitySimulation(): window(nullptr) {}

CitySimulation::~CitySimulation() {
    delete window;
}

