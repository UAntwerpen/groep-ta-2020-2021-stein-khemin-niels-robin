//
// Created by Khemin on 1-5-2021.
//

#include "Citizen.h"

Citizen::Citizen() : Transport() {
    inCar = false;
    string pixArt = "../PixelArt/Pedestrian";
    int random = (rand()%3)+1;
    pixArt = pixArt + to_string(random) + ".png";
    pixelart = pixArt;
}

Citizen::Citizen(Cell *location, Cell *g) : Transport(location, g) {
    inCar = false;
    string pixArt = "../PixelArt/Pedestrian";
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

void Citizen::update(CellulaireAutomaat& city) {
//    int dx = 0;
//    int dy = 0;

//    if (this->getDirection() == 'N') { dx = 0; dy = -1; }
//    if (this->getDirection() == 'E') { dx = 1; dy = 0; }
//    if (this->getDirection() == 'S') { dx = 0; dy = 1; }
//    if (this->getDirection() == 'W') { dx = -1; dy = 0; }
//
//    pair<int, int> currPos = this->getLocation()->getPos();
    pair<int, int> newPos = this->getNextStep();
    Cell* newLoc = city(newPos.first, newPos.second);

    this->setLocation(newLoc);
    this->increaseProgress();

    // Aangekomen op bestemming;
    if (this->getLocation()->getPos() == this->getGoal()->getPos()){
        this->setGoal(nullptr);
        this->setProgress(-1);
        this->setRoute("");
        this->setStatus(false);
    }
}

bool Citizen::getInCar() {
    return inCar;
}

void Citizen::setInCar(bool b) {
    inCar = b;
}
