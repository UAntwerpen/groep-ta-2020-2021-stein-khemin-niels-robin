//
// Created by Khemin on 26-5-2021.
//

#include "Pathfinding.h"
#include "Vehicle.h"
#include "Citizen.h"

void template_main(){
    CellulaireAutomaat* map = new CellulaireAutomaat("map001.txt");

    auto* car = new Vehicle((*map)(1, 0), (*map)(5,4));

    auto* person1 = new Citizen((*map)(2,3));

    cout << person1->getLocation()->getPos().first << ' ' << person1->getLocation()->getPos().second << endl;

    car->addPerson(person1);

    cout << car[0].getLocation()->getPos().first << ' ' << car[0].getLocation()->getPos().second << endl;

    auto* mask = new PFMask(*map, car->getGoal(), true);

    mask->generateMask();

    car->setMask(mask);

    car->calculateRoute();

    cout << car->getRoute() << endl;

//    car->update(*map);
};

