//
// Created by Khemin on 26-5-2021.
//

#include "Pathfinding.h"
#include "Vehicle.h"
#include "Citizen.h"

void template_main(){
    CellulaireAutomaat* map;

    auto* car = new Vehicle(&(*map)(2, 3), &(*map)(5,3));

    auto* person1 = new Citizen(&(*map)(2,3));

    car->addPerson(person1);

    auto* mask = new PFMask(*map, car->getGoal(), true);

    mask->generateMask();

    car->setMask(mask);

    car->calculateRoute();

    cout << car->getRoute() << endl;

    bool displaying;
    while (displaying){
    car->update(*map);
    // sleep / display
    // maybe sleep afhankelijk van speed attribuut maken (EXTRA).
    }
};

