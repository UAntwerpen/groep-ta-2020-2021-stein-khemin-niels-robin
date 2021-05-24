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

void Cell::addPerson(Citizen *person) {

}

std::vector<Citizen *> Cell::getPersons() const {
    return std::vector<Citizen *>();
}

CellulaireAutomaat* Cell::getCellulaireAutomaat() const {
    return this->getCellulaireAutomaat();
}

std::vector<bool> Cell::getRoadConnectPoints() {
    return std::vector<bool>{false,false,false,false};
}

void Cell::updateDaysUntilExpired() {
    std::vector<Cell *>neighbors = this->getCellulaireAutomaat()->getNeighbourhood(this->col, this->row);
    int neighborsExpired = 0;
    for(auto it = neighbors.begin(); it != neighbors.end(); it++){
        if((*it)->isExpired())
            neighborsExpired++;
    }
    this->daysUntilExpired = 1.2 + (0.2 * neighborsExpired) - this->getHappiness();
}

double Cell::isExpired() {
    return this->daysUntilExpired < 0;
}

EStates Vegetation::getState() const {
    return EVegetation;
}

void Vegetation::update() {

}

float Vegetation::getHappiness() const {
    float value = 0;

    //check for houses and other stores in radius
    int stores = this->getCellulaireAutomaat()->count(EStoreZone, row, col, 10)-1;
    int houses = this->getCellulaireAutomaat()->count(EResidentialZone, row, col, 10);
    value -= stores*0.2;
    value += houses*0.2;
    if(houses == 0) value -= 0.5;
    if(stores == 0) value += 0.5;
    //check for road in neighbourhood
    std::vector<Cell*> neighbourhood = this->getCellulaireAutomaat()->getNeighbourhood(row,col);
    bool road = false;
    for(auto it = neighbourhood.begin(); it != neighbourhood.end(); it++){
        if((*it)->getState() == ERoad){
            road = true;
            break;
        }
    }
    if(!road) value -= 2;

    if(value < -1) value = -1;
    if(value > 1) value = 1;
    return value;
}

void Vegetation::drawToScreen(MainWindow *window) {
    window->drawTile(this->getPos().first, this->getPos().second, this->getPixelArt().first, this->getPixelArt().second);
}

std::pair<int, std::string> Vegetation::getPixelArt() {
    return std::pair<int, std::string>(0, pixelArt);
}

EStates Road::getState() const {
    return ERoad;
}

void Road::update() {

}

void Road::addPerson(Citizen *person) {

}

void Road::drawToScreen(MainWindow *window) {
    std::pair<int, std::string> roadPixArt = this->getPixelArt();
    window->drawTile(this->getPos().first, this->getPos().second, roadPixArt.first, roadPixArt.second);
}

std::pair<int, std::string> Road::getPixelArt() {
    std::vector<bool> neighborsRoads = getNeighborsRoads();
    return getCorrectRoad(neighborsRoads);
}

std::pair<int, std::string> Road::getCorrectRoad(std::vector<bool> &roadConnectPoint1) {
    if(!roadConnectPoint1[0] && !roadConnectPoint1[1] && !roadConnectPoint1[2] && !roadConnectPoint1[3]){
        return std::pair<int, std::string>(2, "../PixelArt/Road_Doodlopend.png");
    }
    std::map<std::string,std::vector<bool>> connectionPointCountImage = {
            {"../PixelArt/Road_Doodlopend.png", {true, false, false, false}},
            {"../PixelArt/Road_Bocht.png", {true, true, false, false}},
            {"../PixelArt/Road_Recht.png", {true, false, true, false}},
            {"../PixelArt/Road_Kruispunt.png", {true, true, true, true}},
            {"../PixelArt/Road_T_Kruispunt.png", {true, true, true, false}},
    };

    int rotations = 0;
    while(true){
        for(auto it = connectionPointCountImage.begin(); it != connectionPointCountImage.end(); it++){
            if((*it).second[0] == roadConnectPoint1[0] &&
               (*it).second[1] == roadConnectPoint1[1] &&
               (*it).second[2] == roadConnectPoint1[2] &&
               (*it).second[3] == roadConnectPoint1[3]){
                return std::pair<int, std::string>(rotations, it->first);
            }
            else{
                (*it).second = {(*it).second[3], (*it).second[0],(*it).second[1],(*it).second[2]};
            }
        }
        rotations++;
    }
}

std::vector<bool> Road::getNeighborsRoads() {
    int row = this->getPos().first;
    int col = this->getPos().second;
    CellulaireAutomaat* cellulaireAutomaat = this->getCellulaireAutomaat();

    /*
     * Geeft aan welke zijde verbonden moet worden;
     *  [0]: links        [0]
     *  [1]: rechts      xxxxx
     *  [2]: boven  [3]  xxxxx  [1]
     *  [3]: onder       xxxxx
     *                    [2]
     */
    std::vector<bool> road = {false, false, false, false};
/*
    road[1] = (*cellulaireAutomaat)(row, col + 1).getRoadConnectPoints()[0];
    road[0] = (*cellulaireAutomaat)(row, col - 1).getRoadConnectPoints()[1];
    road[3] = (*cellulaireAutomaat)(row + 1, col).getRoadConnectPoints()[2];
    road[2] = (*cellulaireAutomaat)(row - 1, col).getRoadConnectPoints()[3];*/

    road[1] = (*cellulaireAutomaat)(row, col + 1)->getState() == ERoad;
    road[3] = (*cellulaireAutomaat)(row, col - 1)->getState() == ERoad;
    road[2] = (*cellulaireAutomaat)(row + 1, col)->getState() == ERoad;
    road[0] = (*cellulaireAutomaat)(row - 1, col)->getState() == ERoad;

    return road;
}

EStates ResidentialZone::getState() const {
    return EResidentialZone;
}

void ResidentialZone::update() {

}

float ResidentialZone::getHappiness() const {
    float value = -1;

    //check for store zones and industrial zones
    int stores = this->getCellulaireAutomaat()->count(EStoreZone, row, col, 10);
    int workplaces = this->getCellulaireAutomaat()->count(EIndustrialZone, row, col, 10);
    int parks = this->getCellulaireAutomaat()->count(EVegetation, row, col, 10);
    value += stores*0.2 + workplaces*0.2 + parks*0.1;
    if(stores == 0) value -= 1;
    if(workplaces == 0) value -= 1;
    if(parks == 0) value -= 0.5;

    //check for road in neighbourhood
    std::vector<Cell*> neighbourhood = this->getCellulaireAutomaat()->getNeighbourhood(row,col);
    bool road = false;
    for(auto it = neighbourhood.begin(); it != neighbourhood.end(); it++){
        if((*it)->getState() == ERoad){
            road = true;
            break;
        }
    }
    if(!road) value -= 1;

    if(value < -1) value = -1;
    if(value > 1) value = 1;
    return value;
}

void ResidentialZone::addPerson(Citizen *person) {

}

ResidentialZone::ResidentialZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat) : Cell(row, col, cellulaireAutomaat) {
    building = House();
}

EStates IndustrialZone::getState() const {
    return EIndustrialZone;
}

void IndustrialZone::update() {

}

float IndustrialZone::getHappiness() const {
    float value = 0;

    //check for houses and other Industrial zones in radius
    int workplaces = this->getCellulaireAutomaat()->count(EIndustrialZone, row, col, 10)-1;
    int houses = this->getCellulaireAutomaat()->count(EResidentialZone, row, col, 10);
    value -= workplaces*0.2;
    value += houses*0.2;
    if(houses == 0) value -= 0.5;
    if(workplaces == 0) value += 0.5;
    //check for road in neighbourhood
    std::vector<Cell*> neighbourhood = this->getCellulaireAutomaat()->getNeighbourhood(row,col);
    bool road = false;
    for(auto it = neighbourhood.begin(); it != neighbourhood.end(); it++){
        if((*it)->getState() == ERoad){
            road = true;
            break;
        }
    }
    if(!road) value -= 2;

    if(value < -1) value = -1;
    if(value > 1) value = 1;
    return value;
}

void IndustrialZone::addPerson(Citizen *person) {

}

IndustrialZone::IndustrialZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat) : Cell(row, col, cellulaireAutomaat) {
    building = Workplace();
}

EStates StoreZone::getState() const {
    return EStoreZone;
}

void StoreZone::update() {

}

void StoreZone::addPerson(Citizen *person) {

}

StoreZone::StoreZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat) : Cell(row, col, cellulaireAutomaat) {
    building = Store();
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
