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

bool Cell::isDilapidated() {
    return false;
}

EStates Vegetation::getState() const {
    return EResidentialZone;
}

void Vegetation::update() {

}

float Vegetation::getHappiness() const {
    return 0;
}

void Vegetation::addPerson(Pedestrian *person) {

}

std::vector<Pedestrian *> Vegetation::getPersons() const {
    return std::vector<Pedestrian *>();
}

bool Vegetation::isDilapidated() {
    return Cell::isDilapidated();
}

EStates Road::getState() const {
    return EResidentialZone;
}

void Road::update() {

}

float Road::getHappiness() const {
    return 0;
}

void Road::addPerson(Pedestrian *person) {

}

std::vector<Pedestrian *> Road::getPersons() const {
    return std::vector<Pedestrian *>();
}

bool Road::isDilapidated() {
    return Cell::isDilapidated();
}

EStates ResidentialZone::getState() const {
    return EResidentialZone;
}

void ResidentialZone::update() {

}

float ResidentialZone::getHappiness() const {
    return 0;
}

void ResidentialZone::addPerson(Pedestrian *person) {

}

std::vector<Pedestrian *> ResidentialZone::getPersons() const {
    return std::vector<Pedestrian *>();
}

bool ResidentialZone::isDilapidated() {
    return Cell::isDilapidated();
}

ResidentialZone::ResidentialZone() {

}

EStates IndustrialZone::getState() const {
    return EResidentialZone;
}

void IndustrialZone::update() {

}

float IndustrialZone::getHappiness() const {
    return 0;
}

void IndustrialZone::addPerson(Pedestrian *person) {

}

std::vector<Pedestrian *> IndustrialZone::getPersons() const {
    return std::vector<Pedestrian *>();
}

bool IndustrialZone::isDilapidated() {
    return Cell::isDilapidated();
}

EStates StoreZone::getState() const {
    return EResidentialZone;
}

void StoreZone::update() {

}

float StoreZone::getHappiness() const {
    return 0;
}

void StoreZone::addPerson(Pedestrian *person) {

}

std::vector<Pedestrian *> StoreZone::getPersons() const {
    return std::vector<Pedestrian *>();
}

bool StoreZone::isDilapidated() {
    return Cell::isDilapidated();
}

Cell *CellFactorySingleton::getCell(EStates state) {
    Cell* ret;

    switch (state) {
        case 1:
            ret = new Road;
            break;
        case 2:
            ret = new ResidentialZone;
            break;
        case 3:
            ret = new IndustrialZone;
            break;
        case 4:
            ret = new StoreZone;
        case 0:
        default:
            ret = new Vegetation;
            break;
    }

//        objects.emplace_back(ret);
    return ret;
}

Cell *CellFactorySingleton::getCell(EStates state, Cell* old){
    Cell *ret;

    switch (state) {
        case 1:
            ret = new Road;
            break;
        case 2:
            ret = new ResidentialZone;
            break;
        case 3:
            ret = new IndustrialZone;
            break;
        case 4:
            ret = new StoreZone;
        case 0:
        default:
            ret = new Vegetation;
            break;
    }

    ret->setPos(old->getPos());
    for (const auto &ped: old->getPersons()) {
        ret->addPerson(ped);
    }
    //        objects.emplace_back(ret);
    return ret;
}
