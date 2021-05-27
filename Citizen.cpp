//
// Created by Khemin on 1-5-2021.
//

#include "Citizen.h"

Citizen::Citizen() : Transport() {}

Citizen::Citizen(Cell *location, Cell *g) : Transport(location, g) {}

float Citizen::getHappiness() {
    return happiness;
}

void Citizen::setHappiness(float h) {
    happiness = h;
    ENSURE(this->getHappiness() == h, "setHappiness post condition failure");
}

EStates Citizen::getState() const {
    return ECitizen;
}
