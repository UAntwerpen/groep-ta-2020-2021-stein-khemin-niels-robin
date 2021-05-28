//
// Created by Khemin on 1-5-2021.
//

#include "Transport.h"
#include "Pathfinding.h"
#include <utility>
#include "lib/DesignByContract.h"

Transport::Transport() {

    location = nullptr;
    goal = nullptr;

    mask = new PFMask(0, 0);
    route = "";
    progress = -1;
    direction = 'N';
}

Transport::Transport(Cell *loc, Cell *g) {
    location = loc;
    goal = g;

    mask = new PFMask(0, 0);
    route = "";
    progress = -1;
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

PFMask *Transport::getMask() {
    return mask;
}

void Transport::setMask(PFMask *m) {
    mask = m;
}

string Transport::getRoute() {
    return route;
}

void Transport::setRoute(string r) {
    route = std::move(r);
    progress = 0;
    this->changeDirection();
}

void Transport::calculateRoute() {
    pair<int, int> goalPoss = this->getGoal()->getPos();
    REQUIRE(this->getMask()->getCell(goalPoss.first, goalPoss.second)->getValue() == 0, "incompatible PFMask for this Transport.");

    string result;

    pair<int, int> locCoord = this->getLocation()->getPos();
    PFCell* currCell = this->getMask()->getCell(locCoord.first, locCoord.second);

    while (currCell->getValue() != 0) {
        pair<int, int> currPos = currCell->getPos();
        vector<int> ints = this->getMask()->getNeighbourInts(currPos.first, currPos.second);

        int min = ints[0];
        for (int el : ints) {
            if (el < min) {
                min = el;
            }
        }

        //Prioriseert eerst bewegen naar rechts, gevolgd door onder, links en tenslotte boven. (Als buren zelfde min int value hebben).
        if (currPos.second + 1 < this->getMask()->getWidth() && this->getMask()->getCell(currPos.first, currPos.second + 1)->getValue() == min) {
            result += "E";

            currCell = this->getMask()->getCell(currPos.first, currPos.second + 1);
            continue;
        } else if (currPos.first + 1 < this->getMask()->getHeight() && this->getMask()->getCell(currPos.first + 1, currPos.second)->getValue() == min) {
            result += "S";

            currCell = this->getMask()->getCell(currPos.first + 1, currPos.second);
            continue;
        } else if (currPos.second - 1 >= 0 && this->getMask()->getCell(currPos.first, currPos.second - 1)->getValue() == min) {
            result += "W";

            currCell = this->getMask()->getCell(currPos.first, currPos.second - 1);
            continue;
        } else if (currPos.first - 1 >= 0 && this->getMask()->getCell(currPos.first - 1, currPos.second)->getValue() == min) {
            result += "N";

            currCell = this->getMask()->getCell(currPos.first - 1, currPos.second);
            continue;
        }
    }

    route = result;
    this->changeDirection();
}

int Transport::getProgress() const {
    return progress;
}

void Transport::setProgress(int i) {
    progress = i;

    ENSURE(this->getProgress() == i, "setProgress post condition failure");
}

void Transport::increaseProgress(){
    progress += 1;
    this->changeDirection();
}

char Transport::getDirection() const {
    return direction;
}

void Transport::setDirection(char c) {
    direction = c;

    ENSURE(this->getDirection() == c, "setDirection post condition failure");
}

void Transport::changeDirection() {
//    REQUIRE(not this->getRoute().empty(), "Route is empty when calling changeDirection");

    int index = this->getProgress() + 1;

    if (index < this->getRoute().size()) {
        this->setDirection(this->getRoute()[index]);
        ENSURE(this->getDirection() == this->getRoute()[index], "chanceDirection did not change direction correctly.");
    } else {
        this->setDirection('N');
    }
}

void Transport::update(CellulaireAutomaat& city) {
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
    this->increaseProgress();

    // Aangekomen op bestemming;
    if (this->getLocation() == this->getGoal()){
        this->setGoal(nullptr);
        this->setProgress(-1);
        this->setRoute("");
    }
}


