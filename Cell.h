

#ifndef TA_CELL_H
#define TA_CELL_H

#include <string>
#include <vector>

#include "Lib.h"

class Pedestrian;
class Vehicle;

class Cell {
public:
    Cell();

    Cell(int row, int col);

    virtual ~Cell();

    /*!
     * geeft de gepaste enum waarde terug
     * @return enum waarde
     */
    virtual EStates getState() const = 0;

    /*!
     * update alle entiteiten van de cell
     */
    virtual void update() = 0;

    /*!
     * geeft terug hoeveel happiness een bepaalde cell uitstoot
     * @return
     */
    virtual float getHappiness() const = 0;

    /*!
     * voegt een persoon toe aan een cell
     * @param person
     */
    virtual void addPerson(Pedestrian* person) = 0;

    /*!
     * geeft alle personen terug die op de cell staan
     * @return
     */
    virtual std::vector<Pedestrian*> getPersons() const = 0;

    /*!
     * geeft de postitie van de cell terug
     * @return std::pair<int, int> -> (row, col)
     */
    std::pair<int, int> getPos() const;

    /*!
     * verandert de positie van een cel
     * @param r rij
     * @param c kolom
     */
    void setPos(int r, int c);

    /*!
     * verandert de positie van een cel
     * @param pos std::pair<int, int> -> (row, col)
     */
    void setPos(std::pair<int, int> pos);

private:
    int row;
    int col;

    std::vector<Pedestrian*> people;
};

class Vegetation : public Cell{
public:
    EStates getState() const override;

    void update() override;

    float getHappiness() const override;

    void addPerson(Pedestrian* person) override;

    std::vector<Pedestrian*> getPersons() const override;

private:
    //Building building;
};

class Road : public Cell{
public:
    EStates getState() const override;

    void update() override;

    float getHappiness() const override;

    void addPerson(Pedestrian* person) override;

    std::vector<Pedestrian*> getPersons() const override;
private:
    std::string pixelArt;
    std::vector<Vehicle*> vehicles;
};

class ResidentialZone : public Cell{
public:
    EStates getState() const override;

    void update() override;

    float getHappiness() const override;

    void addPerson(Pedestrian* person) override;

    std::vector<Pedestrian*> getPersons() const override;
    //Building building;
};

class IndustrialZone : public Cell{
public:
    EStates getState() const override;

    void update() override;

    float getHappiness() const override;

    void addPerson(Pedestrian* person) override;

    std::vector<Pedestrian*> getPersons() const override;
    //Building building;
};

class StoreZone : public Cell{
public:
    EStates getState() const override;

    void update() override;

    float getHappiness() const override;

    void addPerson(Pedestrian* person) override;

    std::vector<Pedestrian*> getPersons() const override;
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
        Cell* ret;
        switch (state) {
            case 1:
                ret = new Road;
            case 2:
                ret = new ResidentialZone;
            case 3:
                ret = new IndustrialZone;
            case 4:
                ret = new StoreZone;
            case 0:
            default:
                ret = new Vegetation;
        }
//        objects.emplace_back(ret);
        return ret;
    }

    Cell* getCell(const EStates& state, Cell* old){
        Cell* ret;
        switch (state) {
            case 1:
                ret = new Road;
            case 2:
                ret = new ResidentialZone;
            case 3:
                ret = new IndustrialZone;
            case 4:
                ret = new StoreZone;
            case 0:
            default:
                ret = new Vegetation;
        }
        ret->setPos(old->getPos());
        for (const auto& ped: old->getPersons()){
            ret->addPerson(ped);
        }
//        objects.emplace_back(ret);
        return ret;
    }

//    virtual ~CellFactorySingleton() {
//        for (const auto& cell: objects){
//            delete cell;
//        }
//    }

    CellFactorySingleton(CellFactorySingleton const &) = delete;
    void operator=(CellFactorySingleton const &) = delete;

private:
    CellFactorySingleton() = default;
//    std::vector<Cell*> objects;
};

#endif //TA_CELL_H
