#include <iostream>
#include <algorithm>
#include <iomanip>
#include <QApplication>
#include <QTime>
#include <array>

#include "MainWindow.h"
#include "CellulaireAutomaat.h"
#include "Rules.h"
#include "Pathfinding.h"
#include "settingswindow.h"
#include "Vehicle.h"
#include "Citizen.h"

using namespace std;
int main(int argc, char *argv[]){

    CellulaireAutomaat* map = new CellulaireAutomaat("Maps/map001.txt");

    auto* car = new Vehicle((*map)(1, 0), (*map)(5,4));

    auto* person1 = new Citizen((*map)(2,3));

    car->addPerson(person1);

    auto* mask = new PFMask(*map, car->getGoal(), true);

    mask->generateMask();

    car->setMask(mask);

    car->calculateRoute();

    cout << car->getRoute() << endl;
    cout << "======" << endl;


//    QApplication a(argc, argv);
//    GeneticAlgorith algo(GENOME_SIZE, 10);
//
//    Genome<GENOME_SIZE> rule = algo.run(10);
//    string s;
//    for(char c: rule){
//        s += c;
//    }
//    CellulaireAutomaat A(10,10, s);
//    A.changeCell(0, 5, new Road(0, 5, &A));
//    A.draw();
//
//    return QApplication::exec();
}
