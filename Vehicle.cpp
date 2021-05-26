//
// Created by Khemin on 1-5-2021.
//

#include "Vehicle.h"
#include "Citizen.h"
#include <utility>

Vehicle::Vehicle() : Transport() {
    people = vector<Citizen*>();
}

Vehicle::Vehicle(Cell *location, Cell *g) : Transport(location, g) {
    people = vector<Citizen*>();
}

void Vehicle::setPeople(vector<Citizen *> pass) {
    people = std::move(pass);
}

vector<Citizen *> Vehicle::getPeople() {
    return people;
}

Citizen *Vehicle::operator[](unsigned int ind) {
    return people[ind];
}

void Vehicle::addPerson(Citizen *person) {
    people.push_back(person);
}

void Vehicle::update(CellulaireAutomaat &city) {
    int dx;
    int dy;

    if (this->getDirection() == 'N') { dx = 0; dy = -1; }
    if (this->getDirection() == 'E') { dx = 1; dy = 0; }
    if (this->getDirection() == 'S') { dx = 0; dy = 1; }
    if (this->getDirection() == 'W') { dx = -1; dy = 0; }

    pair<int, int> currPos = this->getLocation()->getPos();
    pair<int, int> newPos = pair<int, int>(currPos.first + dy, currPos.second + dx);
    Cell& newLoc = city(newPos.first, newPos.second);

    this->setLocation(&newLoc);

    // locatie van alle inzittende mee aanpassen.
    for (Citizen* citizen : this->getPeople()){
        citizen->setLocation(&newLoc);
    }

    this->increaseProgress();
    this->changeDirection();

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
