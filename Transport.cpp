//
// Created by Khemin on 1-5-2021.
//

#include "Transport.h"
#include "Pathfinding.h"
#include <utility>
#include "lib/DesignByContract.h"

Transport::Transport() {

    location = std::make_pair(-1,-1);
    goal = std::make_pair(-1,-1);
    inTransit = false;

    mask = new PFMask(0, 0);
    route = "";
    progress = -1;
    direction = ' ';

    home = std::make_pair(-1,-1);
}

Transport::Transport(pair<int, int> loc, pair<int, int> g) {
    location = loc;
    goal = g;
    inTransit = false;

    mask = new PFMask(0, 0);
    route = "";
    progress = -1;
    direction = ' ';

    home = loc;
}

pair<int, int> Transport::getLocation() {
    return location;
}

void Transport::setLocation(pair<int, int> l) {
    location = l;
    ENSURE(this->getLocation() == l, "setLoaction post condition failure");
}

pair<int, int> Transport::getGoal() {
    return goal;
}

void Transport::setGoal(pair<int, int> g) {
    goal = g;
    ENSURE(this->getGoal() == g, "setGoal post condition failure");
}

bool Transport::getStatus() {
    return inTransit;
}

void Transport::setStatus(bool status) {
    inTransit = status;
}

PFMask *Transport::getMask() {
    return mask;
}

void Transport::setMask(PFMask *m) {
    delete mask;
    mask = m;
}

string Transport::getRoute() {
    return route;
}

void Transport::setRoute(string r) {
    route = std::move(r);
    progress = -1;
    inTransit = true;
    this->changeDirection();
}

void Transport::calculateRoute() {
    pair<int, int> goalPoss = this->getGoal();
    REQUIRE(this->getMask()->getCell(goalPoss.first, goalPoss.second)->getValue() == 0, "incompatible PFMask for this Transport.");

    string result;

    pair<int, int> locCoord = this->getLocation();
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

    this->setRoute(result);
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

    if (0 <= index && index < (int) this->getRoute().size()) {
        this->setDirection(this->getRoute()[index]);
        ENSURE(this->getDirection() == this->getRoute()[index], "chanceDirection did not change direction correctly.");
    } else {
        this->setDirection(' ');
    }
}

pair<int, int> Transport::getNextStep() {
    int index = this->getProgress() + 1;
    char nextDirection;
    int dx = 0;
    int dy = 0;

    if (index < (int) this->getRoute().size()) {
        nextDirection = this->getRoute()[index];
    } else {
        nextDirection = ' ';
    }

    if (nextDirection == 'N') { dx = 0; dy = -1; }
    if (nextDirection == 'E') { dx = 1; dy = 0; }
    if (nextDirection == 'S') { dx = 0; dy = 1; }
    if (nextDirection == 'W') { dx = -1; dy = 0; }

    pair<int, int> currPos = this->getLocation();

    return std::make_pair(currPos.first + dy, currPos.second + dx);
}

Transport::~Transport() {

}

pair<int, int> Transport::getHome() {
    return home;
}
