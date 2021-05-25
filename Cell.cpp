//
// Created by nibor on 22/04/2021.
//

#include "Cell.h"
#include "lib/DesignByContract.h"
#include <random>
#include <iostream>
#include "MainWindow.h"
#include "CellulaireAutomaat.h"

Cell::~Cell() {

}

Cell::Cell(int row, int col, CellulaireAutomaat* cellulaireAutomaat) : row(row), col(col), cellulaireAutomaat(cellulaireAutomaat) {
    this->daysUntilExpired = 100;
}

std::pair<int, int> Cell::getPos() const{
    return std::make_pair(row, col);
}

float Cell::getHappiness() const {
    return 0;
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
    this->people.push_back(person);
}

std::vector<Citizen *> Cell::getPersons() const {
    return people;
}

CellulaireAutomaat* Cell::getCellulaireAutomaat() const {
    return cellulaireAutomaat;
}

std::vector<bool> Cell::getRoadConnectPoints() {
    return std::vector<bool>{false,false,false,false};
}

void Cell::updateDaysUntilExpired() {
    std::vector<Cell *>neighbors = this->getCellulaireAutomaat()->getNeighbourhood(this->col, this->row);
    int neighborsExpired = 0;
    for(auto it = neighbors.begin(); it != neighbors.end(); it++){
        if((*it) != nullptr && (*it)->isExpired())
            neighborsExpired++;
    }
    this->daysUntilExpired = 1.2 + (0.2 * neighborsExpired) - this->getHappiness();
}

bool Cell::isExpired() {
    return this->daysUntilExpired < 0;
}

Cell::Cell(const Cell &p2): Cell(p2.row, p2.col, p2.cellulaireAutomaat) {
    this->people = p2.people;
}

EStates Vegetation::getState() const {
    return EVegetation;
}

void Vegetation::update() {
    this->updateDaysUntilExpired();
}

float StoreZone::getHappiness() const {
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


float Vegetation::getHappiness() const {
    float value = 0;
    //check for workplaces in radius
    int workplaces = this->getCellulaireAutomaat()->count(EIndustrialZone, row, col, 10);
    value -= workplaces*0.2;
    if(workplaces == 0) value += 0.4;
    //check for road in neighbourhood
    std::vector<Cell*> neighbourhood = this->getCellulaireAutomaat()->getNeighbourhood(row,col);
    bool road = false;
    for(auto it = neighbourhood.begin(); it != neighbourhood.end(); it++){
        if((*it)->getState() == ERoad){
            road = true;
            break;
        }
    }
    if(!road) value -= 0.5;

    if(value < -1) value = -1;
    if(value > 1) value = 1;
    return value;
}

std::pair<int, std::string> Vegetation::getPixelArt() {
    if(this->isExpired()){
        return std::pair<int, std::string>(0, pixelArtVervallen);
    }
    return std::pair<int, std::string>(0, pixelArt);
}

Vegetation::Vegetation(const Cell &p2) : Cell(p2.getPos().first, p2.getPos().second, p2.getCellulaireAutomaat()) {
    this->people = p2.getPersons();
}

EStates Road::getState() const {
    return ERoad;
}

void Road::update() {
    this->updateDaysUntilExpired();
}

std::pair<int, std::string> Road::getPixelArt() {
    if(this->isExpired()){
        return std::pair<int, std::string>(0, pixelArtVervallen);
    }
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


    //TODO eerst checken of de offset niet out of bounds is!
/*
    road[1] = (*cellulaireAutomaat)(row, col + 1).getRoadConnectPoints()[0];
    road[0] = (*cellulaireAutomaat)(row, col - 1).getRoadConnectPoints()[1];
    road[3] = (*cellulaireAutomaat)(row + 1, col).getRoadConnectPoints()[2];
    road[2] = (*cellulaireAutomaat)(row - 1, col).getRoadConnectPoints()[3];*/
    if(row + 1 < cellulaireAutomaat->getHeight() && col + 1 < cellulaireAutomaat->getWidth())
        road[1] = (*cellulaireAutomaat)(row, col + 1)->getState() == ERoad;
    if(row- 1 > 0 && col - 1 > 0)
        road[3] = (*cellulaireAutomaat)(row, col - 1)->getState() == ERoad;
    if(row + 1 < cellulaireAutomaat->getHeight() && col + 1 < cellulaireAutomaat->getWidth())
        road[2] = (*cellulaireAutomaat)(row + 1, col)->getState() == ERoad;
    if(row - 1 >0 && col - 1 >0)
        road[0] = (*cellulaireAutomaat)(row - 1, col)->getState() == ERoad;

/*    road[1] = (*cellulaireAutomaat)(row, col + 1)->getState() == ERoad;
    road[3] = (*cellulaireAutomaat)(row, col - 1)->getState() == ERoad;
    road[2] = (*cellulaireAutomaat)(row + 1, col)->getState() == ERoad;
    road[0] = (*cellulaireAutomaat)(row - 1, col)->getState() == ERoad;*/

    return road;
}

std::vector<Vehicle *> Road::getVehicles() const {
    return this->vehicles;
}

void Road::addVehicle(Vehicle * v) {
    this->vehicles.push_back(v);
}

void Road::updateDaysUntilExpired() {
    if(this->getCellulaireAutomaat()->count(ERoad, this->row, this->col, 1) <= 0){
        this->daysUntilExpired = 0;
    }
    else{
        Cell::updateDaysUntilExpired();
    }
}

Road::Road(const Cell &p2): Cell(p2.getPos().first, p2.getPos().second, p2.getCellulaireAutomaat()) {
    this->people = p2.getPersons();
}

EStates ResidentialZone::getState() const {
    return EResidentialZone;
}

void ResidentialZone::update() {
    this->updateDaysUntilExpired();
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

ResidentialZone::ResidentialZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat) : Cell(row, col, cellulaireAutomaat) {
    building = House();
}

std::pair<int, std::string> ResidentialZone::getPixelArt() {
    if(this->isExpired())
        return std::pair<int, std::string>(0, this->building.getExpiredPixelArt());
    return std::pair<int, std::string>(0, this->building.getPixelArt());
}

ResidentialZone::ResidentialZone(const Cell &p2): Cell(p2.getPos().first, p2.getPos().second, p2.getCellulaireAutomaat()) {
    this->people = p2.getPersons();
}

EStates IndustrialZone::getState() const {
    return EIndustrialZone;
}

void IndustrialZone::update() {
    this->updateDaysUntilExpired();
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

IndustrialZone::IndustrialZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat) : Cell(row, col, cellulaireAutomaat) {
    building = Workplace();
}

std::pair<int, std::string> IndustrialZone::getPixelArt() {
    if(this->isExpired())
        return std::pair<int, std::string>(0, this->building.getExpiredPixelArt());
    return std::pair<int, std::string>(0, this->building.getPixelArt());
}

IndustrialZone::IndustrialZone(const Cell &p2): Cell(p2.getPos().first, p2.getPos().second, p2.getCellulaireAutomaat()) {
    this->people = p2.getPersons();
}

EStates StoreZone::getState() const {
    return EStoreZone;
}

void StoreZone::update() {
    this->updateDaysUntilExpired();
}

StoreZone::StoreZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat) : Cell(row, col, cellulaireAutomaat) {
    building = Store();
}

std::pair<int, std::string> StoreZone::getPixelArt() {
    if(this->isExpired())
        return std::pair<int, std::string>(0, this->building.getExpiredPixelArt());
    return std::pair<int, std::string>(0, this->building.getPixelArt());
}

StoreZone::StoreZone(const Cell &p2): Cell(p2.getPos().first, p2.getPos().second, p2.getCellulaireAutomaat()) {
    this->people = p2.getPersons();
}

Cell *CellFactorySingleton::getCell(EStates state, Cell* old){
    Cell *ret;

    switch (state) {
        case 1:
            ret = new Road(*old);
            break;
        case 2:
            ret = new ResidentialZone(*old);
            break;
        case 3:
            ret = new IndustrialZone(*old);
            break;
        case 4:
            ret = new StoreZone(*old);
        case 0:
        default:
            ret = new Vegetation(*old);
            break;
    }

    ret->setPos(old->getPos());
    for (const auto &ped: old->getPersons()) {
        ret->addPerson(ped);
    }
    //        objects.emplace_back(ret);
    return ret;
}
