

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

class CellFactorySingleton{
public:
    /*!
     * geeft de enige instance van CellFactorySingleton terug
     * @return reference naar de enige instance van het object
     */
    static CellFactorySingleton &getInstance() {
        static CellFactorySingleton instance;
        return instance;
    }

    Cell* getCell(const EStates& state){
        switch (state) {
            //TODO
            case 1:
                return new Cell; // moet vervangen worden
            case 2:
                return new Cell; // moet vervangen worden
            case 3:
                return new Cell; // moet vervangen worden
            case 4:
                return new Cell; // moet vervangen worden
            case 0:
            default:
                return new Cell;
        }
    }

    CellFactorySingleton(CellFactorySingleton const &) = delete;
    void operator=(CellFactorySingleton const &) = delete;

private:
    CellFactorySingleton()= default;
};

#endif //TA_CELL_H
