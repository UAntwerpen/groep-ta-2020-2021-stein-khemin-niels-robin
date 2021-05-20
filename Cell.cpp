//
// Created by nibor on 22/04/2021.
//

#include "Cell.h"
#include "lib/DesignByContract.h"
#include <random>
#include <iostream>
#include "MainWindow.h"
#include "CellulaireAutomaat.h"

Cell::Cell() {
    row = 0;
    col = 0;
}

Cell::~Cell() {

}

Cell::Cell(int row, int col) : row(row), col(col){}

Cell::Cell(int row, int col, CellulaireAutomaat* cellulaireAutomaat) : row(row), col(col), cellulaireAutomaat(cellulaireAutomaat) {}

std::pair<int, int> Cell::getPos() const{
    return std::make_pair(row, col);
}

void Cell::setPos(int r, int c) {
    REQUIRE(r >= 0, "Row is out of bounds!");
    REQUIRE(c >= 0, "Column is out of bounds!");
    row = r;
    col = c;
}

void Cell::setPos(std::pair<int, int> pos) {
    REQUIRE(pos.first >= 0, "Row is out of bounds!");
    REQUIRE(pos.second >= 0, "Column is out of bounds!");
    row = pos.first;
    col = pos.second;
}

ResidentialZone::ResidentialZone() {
    building = House();
}

bool ResidentialZone::isDilapidated() {
    return building.getVerval() > 0;
}

IndustrialZone::IndustrialZone() {
    building = Workplace();
}

bool IndustrialZone::isDilapidated() {
    return building.getVerval() > 0;
}

StoreZone::StoreZone() {
    building = Store();
}

void Cell::addPerson(Citizen *person) {

}

float Cell::getHappiness() const {
    return 0;
}

std::vector<Citizen *> Cell::getPersons() const {
    return std::vector<Citizen *>();
}

CellulaireAutomaat* Cell::getCellulaireAutomaat() const {
    return cellulaireAutomaat;
}

std::vector<bool> Cell::getRoadConnectPoints() {
    return std::vector<bool>{false,false,false,false};
}

EStates Vegetation::getState() const {
    return EResidentialZone;
}

void Vegetation::update() {

}

float Vegetation::getHappiness() const {
    return 0;
}

void Vegetation::addPerson(Citizen *person) {

}

std::vector<Citizen *> Vegetation::getPersons() const {
    return std::vector<Citizen *>();
}

void Vegetation::drawToScreen(MainWindow *window) {
    window->drawTile(this->getPos().first, this->getPos().second, this->getPixelArt().first, this->getPixelArt().second);
}

std::pair<int, std::string> Vegetation::getPixelArt() {
    return std::pair<int, std::string>(0, pixelArt);
}

EStates Road::getState() const {
    return EResidentialZone;
}

void Road::update() {

}

float Road::getHappiness() const {
    return 0;
}

void Road::addPerson(Citizen *person) {

}

bool Road::isDilapidated() {
    return Cell::isDilapidated();
}

void Road::drawToScreen(MainWindow *window) {
    window->drawTile(this->getPos().first, this->getPos().second, this->getPixelArt().first, this->getPixelArt().second);
}

std::pair<int, std::string> Road::getPixelArt() {
    std::vector<bool> neighborsRoads = getNeighborsRoads();
    return getCorrectRoad(neighborsRoads);
}

std::vector<bool> Road::getRoadConnectPoints() {
    return std::vector<bool>{roadConnectPoints[0], roadConnectPoints[1], roadConnectPoints[2], roadConnectPoints[3]};
}

std::pair<int, std::string> Road::getCorrectRoad(std::vector<bool> &roadConnectPoint) {
    if(!roadConnectPoints[0] && !roadConnectPoints[1] && !roadConnectPoints[2] && !roadConnectPoints[3]){
        this->roadConnectPoints = {false, false, true, false};
        return std::pair<int, std::string>(2, "../PixelArt/Road_Doodlopend.png");
    }
    std::map<std::string,std::vector<bool>> connectionPointCountImage = {
            {"../PixelArt/Road_Doodlopend.png", {false, false, true, false}},
            {"../PixelArt/Road_Bocht.png", {true, false, true, false}},
            {"../PixelArt/Road_Rechte_Lijn.png", {true, true, false, false}},
            {"../PixelArt/Road_Kruispunt.png", {true, true, true, true}},
            {"../PixelArt/Road_T_Kruispunt.png", {true, true, false, true}},
    };

    int rotations = 0;

    while(true){
        for(auto it = connectionPointCountImage.begin(); it != connectionPointCountImage.end(); it++){
            if((*it).second[0] == roadConnectPoints[0] &&
               (*it).second[1] == roadConnectPoints[1] &&
               (*it).second[2] == roadConnectPoints[2] &&
               (*it).second[3] == roadConnectPoints[3]){
                this->roadConnectPoints = {(*it).second[0], (*it).second[1], (*it).second[2], (*it).second[3]};
                return std::pair<int, std::string>(rotations, it->first);
            }
            else{
                //roteer road
                rotations++;
                (*it).second = {(*it).second[3], (*it).second[0],(*it).second[1],(*it).second[2]};
            }
        }
    }
}

Road::Road(int row, int col, CellulaireAutomaat *cellulaireAutomaat) : Cell(row, col, cellulaireAutomaat) {
    //std::vector<bool> neighborsRoads = getNeighborsRoads();
    //this->getCorrectRoad(neighborsRoads);
}

std::vector<bool> Road::getNeighborsRoads() {
    int row = this->getPos().first;
    int col = this->getPos().second;
    CellulaireAutomaat* cellulaireAutomaat = this->getCellulaireAutomaat();

    /*
     * Geeft aan welke zijde verbonden moet worden;
     *  [0]: links        [2]
     *  [1]: rechts      xxxxx
     *  [2]: boven  [0]  xxxxx  [1]
     *  [3]: onder       xxxxx
     *                    [3]
     */
    std::vector<bool> road = {false, false, false, false};

    road[1] = (*cellulaireAutomaat)(row, col + 1).getRoadConnectPoints()[0];
    road[0] = (*cellulaireAutomaat)(row, col - 1).getRoadConnectPoints()[1];
    road[3] = (*cellulaireAutomaat)(row + 1, col).getRoadConnectPoints()[2];
    road[2] = (*cellulaireAutomaat)(row - 1, col).getRoadConnectPoints()[3];

    return road;
}

EStates ResidentialZone::getState() const {
    return EResidentialZone;
}

void ResidentialZone::update() {

}

float ResidentialZone::getHappiness() const {
    return 0;
}

void ResidentialZone::addPerson(Citizen *person) {

}

EStates IndustrialZone::getState() const {
    return EResidentialZone;
}

void IndustrialZone::update() {

}

float IndustrialZone::getHappiness() const {
    return 0;
}

void IndustrialZone::addPerson(Citizen *person) {

}

EStates StoreZone::getState() const {
    return EResidentialZone;
}

void StoreZone::update() {

}

float StoreZone::getHappiness() const {
    return 0;
}

void StoreZone::addPerson(Citizen *person) {

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
