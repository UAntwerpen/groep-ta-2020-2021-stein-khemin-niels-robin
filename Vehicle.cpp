//
// Created by Khemin on 1-5-2021.
//

#include "Vehicle.h"
#include "Citizen.h"
#include <utility>

Vehicle::Vehicle() : Transport() {
    people = vector<Citizen*>();
    string pixArt = "Car";
    int random = (rand()%3)+1;
    pixArt = pixArt + to_string(random) + ".png";
    pixelart = pixArt;
}

Vehicle::Vehicle(Cell *location, Cell *g) : Transport(location, g) {
    people = vector<Citizen*>();
    string pixArt = "Car";
    int random = (rand()%3)+1;
    pixArt = pixArt + to_string(random) + ".png";
    pixelart = pixArt;
}

void Vehicle::setPeople(vector<Citizen *> pass) {
    for (Citizen* citizen : pass) {
        citizen->setLocation(this->getLocation());
    }
    people = std::move(pass);
}

vector<Citizen *> Vehicle::getPeople() {
    return people;
}

Citizen *Vehicle::operator[](unsigned int ind) {
    return people[ind];
}

void Vehicle::addPerson(Citizen *person) {
    person->setLocation(this->getLocation());
    people.push_back(person);
}

void Vehicle::update(CellulaireAutomaat &city) {
    int dx = 0;
    int dy = 0;

    if (this->getDirection() == 'N') { dx = 0; dy = -1; }
    if (this->getDirection() == 'E') { dx = 1; dy = 0; }
    if (this->getDirection() == 'S') { dx = 0; dy = 1; }
    if (this->getDirection() == 'W') { dx = -1; dy = 0; }

    pair<int, int> currPos = this->getLocation()->getPos();
    pair<int, int> newPos = pair<int, int>(currPos.first + dy, currPos.second + dx);
    Cell* newLoc = city(newPos.first, newPos.second);

    this->setLocation(newLoc);

    // locatie van alle inzittende mee aanpassen.
    for (Citizen* citizen : this->getPeople()){
        citizen->setLocation(newLoc);
    }

    this->increaseProgress();

    // Aangekomen op bestemming;
    if (this->getLocation() == this->getGoal()){
        this->setGoal(nullptr);
        this->setProgress(0);
        this->setRoute("");
    }
}

EStates Vehicle::getState() const {
    return EVehicle;
}

const string &Vehicle::getPixelart() const {
    return pixelart;
}
