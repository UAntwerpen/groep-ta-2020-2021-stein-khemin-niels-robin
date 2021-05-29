//
// Created by stein on 25/05/2021.
//

#include "CitySimulation.h"
#include "Vehicle.h"
#include "Citizen.h"
#include "Pathfinding.h"

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

void CitySimulation::runTransportSimulation(CellulaireAutomaat& map, int steps) {
    int currentStep = 0;

    MainWindow w(map.getWidth(), map.getHeight(), &map);
    w.show();

    int rowDim = map.getHeight();
    int colDim = map.getWidth();

    for (int row = 0; row < rowDim; row++){
        for (int col = 0; col < colDim; col++){
            Cell* currCell = map(row, col);

            // Voegt auto per huis toe.
            if (currCell->getState() == EResidentialZone){
                Vehicle* car = new Vehicle(currCell);
                currCell->setCar(car);
            }
        }
    }
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
                    } else if ((rand() % 100) <= 20) {
                        // Voeg een passagier toe aan de auto als de auto leeg is.
                        if (car->getPeople().empty() && !map(row, col)->getPersons().empty()) {
                            car->addPerson(map(row, col)->getPersons().back());
                            map(row, col)->removeCitizen();
                        }

                        Cell* goal = nullptr;
                        if (map(row, col) != car->getHome()) {
                            goal = car->getHome();
                        } else if (pair<int, int>(randRow, randCol) != car->getLocation()->getPos()) {
                            goal = map(randRow, randCol);
                        }

                        car->setGoal(goal);
                        if (car->getGoal() != nullptr) {
                            auto* mask = new PFMask(map, car->getGoal(), true);
                            mask->generateMask();

                            car->setMask(mask);
                            car->calculateRoute();
                            car->update(map);
                        } else {
                            // Auto verplaatst niet. Passagiers worden terug binnen gezet.
                            for (Citizen* pass : car->getPeople()){
                                car->getLocation()->addPerson(pass);

                                if (car->getLocation()->getPos() == car->getHome()->getPos()){
                                    car->setPeople(vector<Citizen*>());
                                }
                            }
                        }
                    }
                }
//                for (int i = 0; i < map(row, col)->getPersons().size(); i++) {
//                    Citizen* person = map(row, col)->getPersons()[i];

//                    if (person->getStatus()) {
//                        person->update(map);
//                    }
//                }
//                if (randRow < 5 && randCol < 5 && (rand() % 100) <= 15 && !map(row, col)->getPersons().empty()) {
//                    Citizen* person = map(row, col)->getPersons().back();


//                    Cell* goal = nullptr;
//                    if (pair<int, int>(randRow, randCol) != person->getLocation()->getPos()) {
//                        goal = map(randRow, randCol);
//                    }

//                    person->setGoal(goal);
//                    if (person->getGoal() != nullptr) {
//                        map(row, col)->removeCitizen();
//                        auto* mask = new PFMask(map, person->getGoal(), false);
//                        mask->generateMask();

//                        person->setMask(mask);
//                        person->calculateRoute();
//                        person->update(map);
//                    }
//                }
            }
        }
        w.updateAll();
        delay(1);
        while(w.getPause()){
            delay(1);
        }
        currentStep += 1;
        if (currentStep % 10 == 0) {
            w.addDay();
        }
    }
}

