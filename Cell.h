

#ifndef TA_CELL_H
#define TA_CELL_H

#include <string>
#include <vector>
#include "Building.h"
#include <map>
#include "Lib.h"
#include "iostream"

class Citizen;
class Vehicle;
class MainWindow;
class CellulaireAutomaat;

class Cell {
public:
    Cell();

    //TODO weg
    Cell(int row, int col);

    //Cel moet omgeving kunnen bepalen
    Cell(int row, int col, CellulaireAutomaat* cellulaireAutomaat);

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
     * draw cell to interface
     */
    virtual void drawToScreen(MainWindow *window){
        std::cout << "fout" << std::endl;
    };

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
     * Geeft voor elke zijde weer of er een weg aan verbonden kan worden;
     *  [0]: links        [2]
     *  [1]: rechts      xxxxx
     *  [2]: boven  [0]  xxxxx  [1]
     *  [3]: onder       xxxxx
     *                    [3]
     */
    virtual std::vector<bool> getRoadConnectPoints();

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
     * geeft de CellulaireAutomaat terug waar de huidige cell een deel van uitmaakt
     * @return CellulaireAutomaat
     */
    CellulaireAutomaat* getCellulaireAutomaat() const;

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

    /*
     * int: rotation, string: pad to pixel art
     */
    virtual std::pair<int, std::string> getPixelArt(){return std::pair<int, std::string>(0, "");};

private:
    int row = 0;
    int col = 0;

    CellulaireAutomaat* cellulaireAutomaat;
    std::vector<Citizen*> people;
};

class Vegetation : public Cell{
public:
    Vegetation(int row, int col, CellulaireAutomaat* cellulaireAutomaat): Cell(row, col, cellulaireAutomaat){}

    //TODO Weg
    Vegetation(){}

    /*
     * Copy constructor
     */
    Vegetation(const Vegetation &V1);

    EStates getState() const override;

    void update() override;

    void drawToScreen(MainWindow *window) override;

    std::pair<int, std::string> getPixelArt() override;

    float getHappiness() const override;

    void addPerson(Citizen* person) override;

    std::vector<Citizen*> getPersons() const override;

private:
    std::string pixelArt = "../PixelArt/Default.png";
};

class Road : public Cell{
public:
    //TODO weg
    Road(){}

    Road(int row, int col, CellulaireAutomaat* cellulaireAutomaat);

    /*
     * Copy constructor
     */
    Road(const Road &R1);

    EStates getState() const override;

    void update() override;

    void drawToScreen(MainWindow *window) override;

    std::pair<int, std::string> getPixelArt() override;

    std::vector<bool> getNeighborsRoads();

    float getHappiness() const override;

    void addPerson(Citizen* person) override;

    //std::vector<Pedestrian*> getPersons() const override;

    bool isDilapidated() override;

    /*!
     * Geeft voor elke zijde weer of er een weg aan verbonden kan worden;
     *  [0]: links        [2]
     *  [1]: rechts      xxxxx
     *  [2]: boven  [0]  xxxxx  [1]
     *  [3]: onder       xxxxx
     *                    [3]
     * @param person
     */
    std::vector<bool> getRoadConnectPoints() override;

private:
    /*
     * returns rotatie en string van weg
     */
    std::pair<int, std::string> getCorrectRoad(std::vector<bool> &roadConnectPoint);
    std::vector<bool> roadConnectPoints = {false, false, false, false};
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
