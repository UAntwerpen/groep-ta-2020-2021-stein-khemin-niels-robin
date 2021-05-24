//
// Created by Khemin on 1-5-2021.
//

#include "Transport.h"

#include <utility>
#include "lib/DesignByContract.h"

Transport::Transport() {

    location = nullptr;
    goal = nullptr;

    route = "";
    progress = 0;
    direction = 'N';
}

Transport::Transport(Cell *loc, Cell *g) {
    location = loc;
    goal = g;

    route = "";
    progress = 0;
    direction = 'N';
}

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
    progress = 0;
    this->changeDirection();
}

void Transport::calculateRoute(PFMask mask) {
    pair<int, int> goalPoss = this->getGoal()->getPos();
    REQUIRE(mask.getCell(goalPoss.first, goalPoss.second).getValue() == 0, "incompatible PFMask for this Transport.");
    //TODO implementatie
}

int Transport::getProgress() {
    return progress;
}

void Transport::setProgress(int i) {
    progress = i;

    ENSURE(this->getProgress() == i, "setProgress post condition failure");
}

void Transport::increaseProgress(){
    progress += 1;

    if (progress < this->getRoute().size()){
        this->changeDirection();
    }
}

char Transport::getDirection() {
    return direction;
}

void Transport::setDirection(char c) {
    direction = c;

    ENSURE(this->getDirection() == c, "setDirection post condition failure");
}

void Transport::changeDirection() {
    REQUIRE(not this->getRoute().empty(), "Route is empty when calling changeDirection");

    int index = this->getProgress();

    if (index < this->getRoute().size()) {
        this->setDirection(this->getRoute()[index]);
        ENSURE(this->getDirection() == this->getRoute()[index], "chanceDirection did not change direction correctly.");
    } else {
        this->setDirection('N');
    }
}

void Transport::update(CellulaireAutomaat& city) {
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
    this->increaseProgress();
    this->changeDirection();

    // Aangekomen op bestemming;
    if (this->getLocation() == this->getGoal()){
        this->setGoal(nullptr);
        this->setProgress(0);
        this->setRoute("");
    }
}
