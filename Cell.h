

#ifndef TA_CELL_H
#define TA_CELL_H

#include "Lib.h"
#include <string>
#include <vector>
#include "Vehicle.h"

class Cell {
public:
    Cell();

    virtual EStates getState();

    double getHappiness();

private:
    int row;
    int col;

    std::vector<Peaple*> peaple;
};

class Vegetation : public Cell{
private:
    //Building building;
};

class Road : public Cell{
private:
    std::string pixelArt;
    std::vector<Vehicle*> vehicles;
};

class ResidentialZone : public Cell{
    //Building building;
};

class IndustrialZone : public Cell{
    //Building building;
};

class StoreZone : public Cell{
    //Building building;
};
#endif //TA_CELL_H
