//
// Created by nibor on 22/04/2021.
//

#include "Cell.h"
#include <random>

Cell::Cell() {
    row = 0;
    col = 0;
}

Cell::~Cell() {

}

Cell::Cell(int row, int col) : row(row), col(col) {}

std::pair<int, int> Cell::getPos() const{
    return std::make_pair(row, col);
}

void Cell::setPos(int r, int c) {
    row = r;
    col = c;
}

void Cell::setPos(std::pair<int, int> pos) {
    row = pos.first;
    col = pos.second;
}

