//
// Created by Khemin on 9-5-2021.
//

#include "PathfindingCell.h"

PFCell::PFCell(bool passable, bool goal, int value) : passable(passable), goal(goal), value(value) {}

bool PFCell::getPassable() const { return passable; }

void PFCell::setPassable(bool p) {
    passable = p;
    ENSURE(this->getPassable() == p, "setPassable post condition failure");
}

bool PFCell::getGoal() const { return goal; }

void PFCell::setGoal(bool g) {
    goal = g;
    ENSURE(this->getGoal() == g, "setGoal post condition failure");
}

int PFCell::getValue() const {
    REQUIRE(this->getPassable() == true, "Only passable PathfindingCells have integer values.");
    return value;
}

void PFCell::setValue(int v) {
    value = v;
    ENSURE(this->getValue() == v, "setValue post condition failure");
}