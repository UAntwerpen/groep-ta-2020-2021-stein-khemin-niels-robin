//
// Created by nibor on 22/04/2021.
//
#include <random>
#include <iostream>
#include <algorithm>

#include "Cell.h"
#include "lib/DesignByContract.h"
#include "CellulaireAutomaat.h"
#include "Citizen.h"
#include "Vehicle.h"

Cell::~Cell() {

}

Cell::Cell(int row, int col, CellulaireAutomaat *cellulaireAutomaat) : row(row), col(col),
                                                                       cellulaireAutomaat(cellulaireAutomaat) {
    this->daysUntilExpired = (rand() % 200) + 60;
}

std::pair<int, int> Cell::getPos() const {
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
    this->people.push_back(person);
}

std::vector<Citizen *> Cell::getPersons() const {
    return people;
}

CellulaireAutomaat *Cell::getCellulaireAutomaat() const {
    return cellulaireAutomaat;
}

std::vector<bool> Cell::getRoadConnectPoints() {
    return std::vector<bool>{false, false, false, false};
}

void Cell::updateDaysUntilExpired() {
    std::vector<Cell *> neighbors = this->getCellulaireAutomaat()->getNeighbourhood(this->col, this->row);
    int neighborsExpired = 0;
    for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
        if ((*it) != nullptr && (*it)->isExpired())
            neighborsExpired++;
    }
    this->daysUntilExpired -= (0.2 * neighborsExpired);
    this->daysUntilExpired -= 5 - this->getHappiness();
}

bool Cell::isExpired() {
    return this->daysUntilExpired < 0;
}

Cell::Cell(const Cell &p2) : Cell(p2.row, p2.col, p2.cellulaireAutomaat) {
    this->people = p2.people;
}

std::vector<bool> Cell::getNeighborsRoads() {
    /*
     * Geeft aan welke zijde verbonden moet worden;
     *  [0]: links        [0]
     *  [1]: rechts      xxxxx
     *  [2]: boven  [3]  xxxxx  [1]
     *  [3]: onder       xxxxx
     *                    [2]
     */
    std::vector<bool> road = {false, false, false, false};


    if (row < cellulaireAutomaat->getHeight() && col + 1 < cellulaireAutomaat->getWidth())
        road[1] = (*cellulaireAutomaat)(row, col + 1)->getState() == ERoad;

    if (row >= 0 && col - 1 >= 0)
        road[3] = (*cellulaireAutomaat)(row, col - 1)->getState() == ERoad;

    if (row + 1 < cellulaireAutomaat->getHeight() && col < cellulaireAutomaat->getWidth())
        road[2] = (*cellulaireAutomaat)(row + 1, col)->getState() == ERoad;

    if (row - 1 >= 0 && col >= 0)
        road[0] = (*cellulaireAutomaat)(row - 1, col)->getState() == ERoad;

    return road;
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
    /*
    int stores = this->getCellulaireAutomaat()->count(EStoreZone, row, col, 10) - 1;
    int houses = this->getCellulaireAutomaat()->count(EResidentialZone, row, col, 10);
    value -= stores * 0.2;
    value += houses * 0.2;
    if (houses == 0) value -= 0.5;
    if (stores == 0) value += 0.5;*/

    //check for store zones and industrial zones
    int stores = this->getCellulaireAutomaat()->count(EStoreZone, row, col, 10);
    int houses = this->getCellulaireAutomaat()->count(EResidentialZone, row, col, 10);
    value -= stores * 0.8;
    value += houses * 0.2;
    if (houses == 0) value -= 0.5;
    if (stores == 0) value += 0.5 * houses;

    //check for road in neighbourhood
    std::vector<Cell *> neighbourhood = this->getCellulaireAutomaat()->getNeighbourhood(row, col);
    bool road = false;
    for (auto it = neighbourhood.begin(); it != neighbourhood.end(); it++) {
        if ((*it) != nullptr && (*it)->getState() == ERoad) {
            road = true;
            break;
        }
    }
    if (!road) value -= 2;

    return value;
}

bool Cell::isConnectedTo(int rowTo, int colTo, std::vector<std::pair<int, int>> *roads, bool main) {
    if (this->row == rowTo && this->col == colTo) {
        return true;
    }

    if (main && roads == nullptr) {
        roads = new std::vector<std::pair<int, int>>();
    }

    std::vector<bool> neighborsRoadsBool = this->getNeighborsRoads();
    std::vector<Cell *> neighborsRoad;

    if (neighborsRoadsBool[0])
        neighborsRoad.push_back((*cellulaireAutomaat)(this->row - 1, this->col));

    if (neighborsRoadsBool[1])
        neighborsRoad.push_back((*cellulaireAutomaat)(this->row, this->col + 1));

    if (neighborsRoadsBool[2])
        neighborsRoad.push_back((*cellulaireAutomaat)(this->row + 1, this->col));

    if (neighborsRoadsBool[3])
        neighborsRoad.push_back((*cellulaireAutomaat)(this->row, this->col - 1));

    for (auto it = neighborsRoad.begin(); it != neighborsRoad.end(); it++) {
        if (std::find(roads->begin(), roads->end(), std::pair<int, int>((*it)->row, (*it)->col)) == roads->end()) {
            roads->push_back(std::pair<int, int>((*it)->row, (*it)->col));
            if ((*it)->isConnectedTo(rowTo, colTo, roads, false)) {
                if (main)
                    delete roads;
                return true;
            }
        }
    }
    if (main)
        delete roads;
    return false;
}

Cell *Cell::bestAlternativeCell() {
    Cell* newGround = nullptr;

    Vegetation vegetationTestZone(this->row, this->col, this->getCellulaireAutomaat());
    float vegetationHappiness = vegetationTestZone.getHappiness();

    Road roadTestZone(this->row, this->col, this->getCellulaireAutomaat());
    float roadHappiness = roadTestZone.getHappiness();

    IndustrialZone industrialTestZone(this->row, this->col, this->getCellulaireAutomaat());
    float IndustrialHappiness = industrialTestZone.getHappiness();

    ResidentialZone residentialTestZone(this->row, this->col, this->getCellulaireAutomaat());
    float residentialHappiness = residentialTestZone.getHappiness();

    StoreZone storeTestZone(this->row, this->col, this->getCellulaireAutomaat());
    float storeHappiness = storeTestZone.getHappiness();

    if(vegetationHappiness > roadHappiness &&
       vegetationHappiness > IndustrialHappiness &&
       vegetationHappiness > residentialHappiness &&
       vegetationHappiness > storeHappiness){
        newGround = new Vegetation(this->row, this->col, this->getCellulaireAutomaat());
    }
    else if(IndustrialHappiness > vegetationHappiness &&
            IndustrialHappiness > roadHappiness &&
            IndustrialHappiness > residentialHappiness &&
            IndustrialHappiness > storeHappiness){
        newGround = new IndustrialZone(this->row, this->col, this->getCellulaireAutomaat());
    }
    else if(storeHappiness > vegetationHappiness &&
            storeHappiness > roadHappiness &&
            storeHappiness > residentialHappiness &&
            storeHappiness > IndustrialHappiness){
        newGround = new StoreZone(this->row, this->col, this->getCellulaireAutomaat());
    }
    else if(roadHappiness > vegetationHappiness &&
            roadHappiness > IndustrialHappiness &&
            roadHappiness > residentialHappiness &&
            roadHappiness > storeHappiness){
        newGround = new Road(this->row, this->col, this->getCellulaireAutomaat());
    }
    else{
        newGround = new ResidentialZone(this->row, this->col, this->getCellulaireAutomaat());
    }
    return newGround;
}

Vehicle *Cell::getCar() {
    return nullptr;
}

void Cell::setCar(Vehicle *vehicle) {}

float Vegetation::getHappiness() const {
    float value = 0;
    //check for workplaces in radius

    int vegitation = this->getCellulaireAutomaat()->count(EVegetation, row, col, 10);
    int stores = this->getCellulaireAutomaat()->count(EStoreZone, row, col, 10);
    int workplaces = this->getCellulaireAutomaat()->count(EIndustrialZone, row, col, 10);
    int houses = this->getCellulaireAutomaat()->count(EResidentialZone, row, col, 10);
    value += workplaces * 0.01;
    value += stores * 0.01;
    value += houses * 0.01;
    value -= vegitation * 0.15;

    //check for road in neighbourhood
    std::vector<Cell *> neighbourhood = this->getCellulaireAutomaat()->getNeighbourhood(row, col);
    bool road = false;
    for (auto it = neighbourhood.begin(); it != neighbourhood.end(); it++) {
        if ((*it) != nullptr && (*it)->getState() == ERoad) {
            road = true;
            break;
        }
    }
    if (!road) value -= 10;
/*
    if (value < -1) value = -1;
    if (value > 1) value = 1;*/
    return value;
}

std::pair<int, std::string> Vegetation::getPixelArt() {
    if (this->isExpired()) {
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
    if (this->isExpired()) {
        //return std::pair<int, std::string>(0, pixelArtVervallen);
    }
    std::vector<bool> neighborsRoads = getNeighborsRoads();
    return getCorrectRoad(neighborsRoads);
}

std::pair<int, std::string> Road::getCorrectRoad(std::vector<bool> &roadConnectPoint1) {
    if (!roadConnectPoint1[0] && !roadConnectPoint1[1] && !roadConnectPoint1[2] && !roadConnectPoint1[3]) {
        return std::pair<int, std::string>(2, "../PixelArt/Road_Broken.png");
    }
    std::map<std::string, std::vector<bool>> connectionPointCountImage = {
            {"../PixelArt/Road_Doodlopend.png",  {true, false, false, false}},
            {"../PixelArt/Road_Bocht.png",       {true, true,  false, false}},
            {"../PixelArt/Road_Recht.png",       {true, false, true,  false}},
            {"../PixelArt/Road_Kruispunt.png",   {true, true,  true,  true}},
            {"../PixelArt/Road_T_Kruispunt.png", {true, true,  true,  false}},
    };

    int rotations = 0;
    while (true) {
        for (auto it = connectionPointCountImage.begin(); it != connectionPointCountImage.end(); it++) {
            if ((*it).second[0] == roadConnectPoint1[0] &&
                (*it).second[1] == roadConnectPoint1[1] &&
                (*it).second[2] == roadConnectPoint1[2] &&
                (*it).second[3] == roadConnectPoint1[3]) {
                return std::pair<int, std::string>(rotations, it->first);
            } else {
                (*it).second = {(*it).second[3], (*it).second[0], (*it).second[1], (*it).second[2]};
            }
        }
        rotations++;
    }
}

void Road::addVehicle(Vehicle * v) {
    this->vehicles.push_back(v);
}

void Road::updateDaysUntilExpired() {
    int roadCount = this->getCellulaireAutomaat()->count(ERoad, this->row, this->col, 1);
    if (roadCount <= 0) {
        this->daysUntilExpired = 0;
    } else if(roadCount > 4){
        this->daysUntilExpired -= 2;
    }
}

Road::Road(const Cell &p2) : Cell(p2.getPos().first, p2.getPos().second, p2.getCellulaireAutomaat()) {
    this->people = p2.getPersons();
}

float Road::getHappiness() const {
    int roadCount = this->getCellulaireAutomaat()->count(ERoad, this->row, this->col, 1);
    if (roadCount == 1) {
        return +200;
    } else if(roadCount > 5){
        return -200;
    }
    return 1;
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
    int houses = this->getCellulaireAutomaat()->count(EResidentialZone, row, col, 10);
    value += stores * 0.2;
    value += workplaces * 0.2;
    value += parks * 0.2;
    value += houses * 0.2;

    if(stores == 0){
        value -= 1 * houses;
    }
    //check for road in neighbourhood
    std::vector<Cell *> neighbourhood = this->getCellulaireAutomaat()->getNeighbourhood(row, col);
    bool road = false;
    for (auto it = neighbourhood.begin(); it != neighbourhood.end(); it++) {
        if ((*it) != nullptr && (*it)->getState() == ERoad) {
            road = true;
            break;
        }
    }
    if (!road) value -= 1;

    if (value < -1) value = -1;
    if (value > 1) value = 1;
    return value;
}

ResidentialZone::ResidentialZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat) : Cell(row, col,
                                                                                                  cellulaireAutomaat) {
    for (int i = 0; i < 4; i++) {
        Citizen* resident = new Citizen(this->getPos());
        people.push_back(resident);
    }
    building = House();
    car = new Vehicle(this->getPos());
}
std::pair<int, std::string> ResidentialZone::getPixelArt() {
    if (this->isExpired())
        return std::pair<int, std::string>(0, this->building.getExpiredPixelArt());
    return std::pair<int, std::string>(0, this->building.getPixelArt());
}

ResidentialZone::ResidentialZone(const Cell &p2) : Cell(p2.getPos().first, p2.getPos().second,
                                                        p2.getCellulaireAutomaat()) {
    if (p2.getPersons().empty()) {
        for (int i = 0; i < 4; i++) {
            Citizen* resident = new Citizen(this->getPos());
            people.push_back(resident);
        }
    } else {
        this->people = p2.getPersons();
    }
    building = House();
    car = new Vehicle(this->getPos());
}

Vehicle *ResidentialZone::getCar() {
    return car;
}

void ResidentialZone::setCar(Vehicle *vehicle) {
    car = vehicle;
}

ResidentialZone::~ResidentialZone() {
    delete car;
    for(auto it = this->people.begin(); it != this->people.end(); it++){
        delete (*it);
    }
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
    int workplaces = this->getCellulaireAutomaat()->count(EIndustrialZone, row, col, 10) - 1;
    int houses = this->getCellulaireAutomaat()->count(EResidentialZone, row, col, 10);
    value -= workplaces * 0.4;
    value += houses * 0.2;
    if (houses == 0) value -= 0.5;
    if (workplaces == 0) value += 0.5;
    //check for road in neighbourhood
    std::vector<Cell *> neighbourhood = this->getCellulaireAutomaat()->getNeighbourhood(row, col);
    bool road = false;
    for (auto it = neighbourhood.begin(); it != neighbourhood.end(); it++) {
        if ((*it) != nullptr && (*it)->getState() == ERoad) {
            road = true;
            break;
        }
    }
    if (!road) value -= 5;

    return value;
}

IndustrialZone::IndustrialZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat) : Cell(row, col,
                                                                                                cellulaireAutomaat) {
    building = Workplace();
}

std::pair<int, std::string> IndustrialZone::getPixelArt() {
    if (this->isExpired())
        return std::pair<int, std::string>(0, this->building.getExpiredPixelArt());
    return std::pair<int, std::string>(0, this->building.getPixelArt());
}

IndustrialZone::IndustrialZone(const Cell &p2) : Cell(p2.getPos().first, p2.getPos().second,
                                                      p2.getCellulaireAutomaat()) {
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
    if (this->isExpired())
        return std::pair<int, std::string>(0, this->building.getExpiredPixelArt());
    return std::pair<int, std::string>(0, this->building.getPixelArt());
}

StoreZone::StoreZone(const Cell &p2) : Cell(p2.getPos().first, p2.getPos().second, p2.getCellulaireAutomaat()) {
    this->people = p2.getPersons();
}
