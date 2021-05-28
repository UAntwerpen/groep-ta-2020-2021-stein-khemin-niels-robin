//
// Created by Khemin on 9-5-2021.
//

#include "PFCell.h"

PFCell::PFCell() : Cell(0,0, nullptr) {
    passable = false;
    goal = false;
    value = std::numeric_limits<int>::max();
}

PFCell::PFCell(bool passable, int row, int col, bool goal) : Cell(row, col, nullptr), passable(passable), goal(goal) {
    if (goal) {
        value = 0;
    }
    else if (passable) {
        value = rand()%10000 + 1;
    } else {
        value = std::numeric_limits<int>::max();
    }
}

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
    return value;
}

void PFCell::setValue(int v) {
    value = v;
    ENSURE(this->getValue() == v, "setValue post condition failure");
}

bool PFCell::updatePFCell(int min) {
    if (passable && !goal && min + 1 != this->getValue()) {
        this->value = min + 1;
        return true;
    }
    return false;
}

EStates PFCell::getState() const {
    return EPFCell;
}

void PFCell::update() {
    //* Does Nothing *//
}

PFCell::~PFCell() = default;


