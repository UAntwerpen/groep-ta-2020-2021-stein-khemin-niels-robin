//
// Created by Khemin on 1-5-2021.
//

#include "Transport.h"

#include <utility>
#include "lib/DesignByContract.h"

Cell *Transport::getLocation() {
    return location;
}

void Transport::setLocation(Cell *cell) {
    location = cell;
    ENSURE(this->getLocation() == cell, "setLoaction post condition failure");
}

Cell *Transport::getGoal() {
    return goal;
}

void Transport::setGoal(Cell *cell) {
    goal = cell;
    ENSURE(this->getGoal() == cell, "setGoal post condition failure");
}

string Transport::getRoute() {
    return route;
}

void Transport::setRoute(string r) {
    route = std::move(r);
}

void Transport::update(CellulaireAutomaat& city, char direction) {
    int dx;
    int dy;

    if (direction == 'U') { dx = 0; dy = -1; }
    if (direction == 'R') { dx = 1; dy = 0; }
    if (direction == 'D') { dx = 0; dy = 1; }
    if (direction == 'L') { dx = -1; dy = 0; }

    pair<int, int> currPos = this->getLocation()->getPos();
    pair<int, int> newPos = pair<int, int>(currPos.first + dy, currPos.second + dx);
    //TODO werkt niet (geeft error)
    /*
    Cell& newLoc = city(newPos.first, newPos.second);

    this->setLocation(&newLoc);
    */
}
