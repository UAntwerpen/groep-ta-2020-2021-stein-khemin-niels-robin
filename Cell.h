

#ifndef TA_CELL_H
#define TA_CELL_H

#include <string>
#include <vector>
#include "Building.h"

#include "Lib.h"

class Citizen;
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
     * @return float
     */
    virtual float getHappiness() const;

    /*!
     * voegt een persoon toe aan een cell
     * @param person
     */
    virtual void addPerson(Citizen* person);

    /*!
     * geeft alle personen terug die op de cell staan
     * @return
     */
    virtual std::vector<Citizen*> getPersons() const;

    /*!
     * geeft de postitie van de cell terug
     * @return std::pair<int, int> -> (row, col)
     */
    std::pair<int, int> getPos() const;

    /*!
     * verandert de positie van een cel
     * @param r rij
     * @param c kolom
     * \n REQUIRE(r >= 0, "Row is out of bounds!");
     * \n REQUIRE(c >= 0, "Column is out of bounds!");
     */
    void setPos(int r, int c);

    /*!
     * verandert de positie van een cel
     * @param pos std::pair<int, int> -> (row, col)
     */
    void setPos(std::pair<int, int> pos);

    virtual bool isDilapidated() {return false;};

private:
    int row;
    int col;

    std::vector<Citizen*> people;
};

class Vegetation : public Cell{
public:
    Vegetation();

    /*
     * Copy constructor
     */
    Vegetation(const Vegetation &V1);

    EStates getState() const override;

    void update() override;

    float getHappiness() const override;

    void addPerson(Citizen* person) override;

    std::vector<Citizen*> getPersons() const override;

private:
    //Building building;
};

class Road : public Cell{
public:
    Road();

    /*
     * Copy constructor
     */
    Road(const Road &R1);

    EStates getState() const override;

    void update() override;

    float getHappiness() const override;

    void addPerson(Citizen* person) override;

    //std::vector<Pedestrian*> getPersons() const override;

    bool isDilapidated() override;

private:
    std::string pixelArt;
    std::vector<Vehicle*> vehicles;
    int verval;
};

class ResidentialZone : public Cell{
private:
    House building;
public:
    ResidentialZone();

    /*
     * Copy constructor
     */
    ResidentialZone(const ResidentialZone &R1);

    EStates getState() const override;

    void update() override;

    float getHappiness() const override;

    void addPerson(Citizen* person) override;

    //std::vector<Pedestrian*> getPersons() const override;

    bool isDilapidated() override;
};

class IndustrialZone : public Cell{
private:
    Workplace building;
public:
    IndustrialZone();

    /*
     * Copy constructor
     */
    IndustrialZone(const IndustrialZone &I1);

    EStates getState() const override;

    void update() override;

    float getHappiness() const override;

    void addPerson(Citizen* person) override;

    //std::vector<Pedestrian*> getPersons() const override;

    bool isDilapidated() override;
};

class StoreZone : public Cell{
private:
    Store building;
public:
    StoreZone();

    /*
     * Copy constructor
     */
    StoreZone(const StoreZone &S1);

    EStates getState() const override;

    void update() override;

    float getHappiness() const override;

    void addPerson(Citizen* person) override;

    //std::vector<Pedestrian*> getPersons() const override;

    bool isDilapidated() override;
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

    Cell* getCell(EStates state);

    Cell* getCell(EStates state, Cell* old);

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
