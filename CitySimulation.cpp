//
// Created by stein on 25/05/2021.
//

#include "CitySimulation.h"
#include "Vehicle.h"
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

                std::cout << randRow << ' ' << randCol << std::endl;

                if (map(row, col)->getState() == EResidentialZone){
                    Vehicle* car = map(row, col)->getCar();

                    if (car->getStatus()) {
                        car->update(map);
                    } else if ((rand() % 100) <= 50) {
                        if (car->getPeople().empty()) {
                            int selectPerson = rand() % (map(row, col)->getPersons().size());
                            car->addPerson(map(row, col)->getPersons()[selectPerson]);
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
                        }
                    }
                }
            }
        }

        std::cout << "=================================" << std::endl;
        w.updateAll();
        currentStep += 1;
        if (currentStep % 10 == 0) {
            w.addDay();
        }
    }
}
