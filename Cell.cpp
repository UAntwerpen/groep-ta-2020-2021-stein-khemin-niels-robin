//
// Created by nibor on 22/04/2021.
//

#include "Cell.h"
#include <random>
#include <iostream>

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

Cell *CellFactorySingleton::getCell(EStates state) {
    Cell* ret;

    if (state == 1) ret = new Road;
    else if (state == 2) ret = new ResidentialZone;
    else if (state == 3) ret = new IndustrialZone;
    else if (state == 4) ret = new StoreZone;
    else ret = new Vegetation;
//        objects.emplace_back(ret);
    return nullptr;
}

Cell *CellFactorySingleton::getCell(EStates state, Cell* old){
    Cell *ret;

    if (state == 1) ret = new Road;
    else if (state == 2) ret = new ResidentialZone;
    else if (state == 3) ret = new IndustrialZone;
    else if (state == 4) ret = new StoreZone;
    else ret = new Vegetation;

    ret->setPos(old->getPos());
    for (const auto &ped: old->getPersons()) {
        ret->addPerson(ped);
    }
    //        objects.emplace_back(ret);
    return nullptr;
}
