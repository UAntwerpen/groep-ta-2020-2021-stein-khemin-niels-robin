//
// Created by Khemin on 1-5-2021.
//

#include "Vehicle.h"
#include "Citizen.h"
#include <utility>

Vehicle::Vehicle() : Transport() {
    people = vector<Citizen*>();

    string pixArt = "../PixelArt/Car";
    int random = (rand()%3)+1;
    pixArt = pixArt + to_string(random) + ".png";
    pixelart = pixArt;
}

Vehicle::Vehicle(Cell *location, Cell *g) : Transport(location, g) {
    people = vector<Citizen*>();

    string pixArt = "../PixelArt/Car";
    int random = (rand()%3)+1;
    pixArt = pixArt + to_string(random) + ".png";
    pixelart = pixArt;
}

vector<Citizen *> Vehicle::getPeople() {
    return people;
}

void Vehicle::setPeople(vector<Citizen *> pass) {
    for (Citizen* citizen : pass) {
        citizen->setLocation(this->getLocation());
    }
    people = std::move(pass);
}

Citizen *Vehicle::operator[](unsigned int ind) {
    return people[ind];
}

void Vehicle::addPerson(Citizen *person) {
    person->setLocation(this->getLocation());
    person->setInCar(true);
    people.push_back(person);
}

void Vehicle::update(CellulaireAutomaat &city) {
//    int dx = 0;
//    int dy = 0;

//    if (this->getDirection() == 'N') { dx = 0; dy = -1; }
//    if (this->getDirection() == 'E') { dx = 1; dy = 0; }
//    if (this->getDirection() == 'S') { dx = 0; dy = 1; }
//    if (this->getDirection() == 'W') { dx = -1; dy = 0; }
//
//    pair<int, int> currPos = this->getLocation()->getPos();
    pair<int, int> newPos = this->getNextStep();

    // move is out of bounds TP home
    if (newPos.first < 0 || newPos.first >= city.getHeight() || newPos.second < 0 || newPos.second >= city.getWidth()) {
        this->setLocation(this->getHome());
        this->setGoal(nullptr);
        this->setProgress(-1);
        this->setRoute("");
        this->setStatus(false);
        this->removePassengers();
    }

    Cell* newLoc = city(newPos.first, newPos.second);

    this->setLocation(newLoc);

    // locatie van alle inzittende mee aanpassen.
    for (Citizen* citizen : this->getPeople()){
        citizen->setLocation(newLoc);
    }

    this->increaseProgress();

    // Aangekomen op bestemming;
    if (this->getLocation()->getPos() == this->getGoal()->getPos()){
        this->setGoal(nullptr);
        this->setProgress(-1);
        this->setRoute("");
        this->setStatus(false);

        if (this->getLocation()->getPos() == this->getHome()->getPos()){
            this->removePassengers();
        }
    }
}

EStates Vehicle::getState() const {
    return EVehicle;
}

const string &Vehicle::getPixelart() const {
    return pixelart;
}

void Vehicle::removePassengers() {
    for (Citizen* pass : this->getPeople()) {
        pass->setInCar(false);
    }
    this->setPeople(vector<Citizen*>());
}
