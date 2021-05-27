//
// Created by Khemin on 1-5-2021.
//

#include "Citizen.h"

Citizen::Citizen(){
    string pixArt = "Pedestrian";
    int random = (rand()%3)+1;
    pixArt = pixArt + to_string(random) + ".png";
    pixelart = pixArt;
}

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

const string &Citizen::getPixelart() const {
    return pixelart;
}
