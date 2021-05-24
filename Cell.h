

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

    Cell(const Cell &p2);

    //TODO weg
    Cell(int row, int col);

    //Cel moet omgeving kunnen bepalen
    Cell(int row, int col, CellulaireAutomaat* cellulaireAutomaat);

    virtual ~Cell();

    /*!
     * geeft de gepaste enum waarde terug
     * @return enum waarde
     */
    virtual EStates getState() const{
        return EPFCell;
    }

    /*!
     * updateRules alle entiteiten van de cell
     */
    virtual void update() = 0;

    /*!
     * draw cell to interface
     */
    virtual void drawToScreen(MainWindow *window){
        std::cout << "fout" << std::endl;
    };

    /*!
     * geeft terug hoeveel happiness een bepaalde cell uitstoot (tussen -1 en 1)
     * @return float
     */
    virtual float getHappiness() const;

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
    * voegt een persoon toe aan een cell
    * @param person
    */
    void addPerson(Citizen* person);

    /*!
     * geeft alle personen terug die op de cell staan
     * @return
     */
    std::vector<Citizen*> getPersons() const;

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

    bool isExpired();

    /*
     * int: rotation, string: pad to pixel art
     */
    virtual std::pair<int, std::string> getPixelArt(){return std::pair<int, std::string>(0, "");};

protected:
    int row = 0;
    int col = 0;
    double daysUntilExpired = 0;

    CellulaireAutomaat* cellulaireAutomaat;
    std::vector<Citizen*> people;
    void updateDaysUntilExpired();
};

class Vegetation : public Cell{
public:
    Vegetation(int row, int col, CellulaireAutomaat* cellulaireAutomaat): Cell(row, col, cellulaireAutomaat){}

    //TODO Weg
    Vegetation(){}

    EStates getState() const override;

    void update() override;

    void drawToScreen(MainWindow *window) override;

    std::pair<int, std::string> getPixelArt() override;

    float getHappiness() const override;

private:
    std::string pixelArt = "../PixelArt/Park.png";
    std::string pixelArtVervallen = "../PixelArt/Park_Broken.png";
};

class Road : public Cell{
public:
    //TODO weg
    Road(){std::cout << "FOUT!" << std::endl;}

    Road(int row, int col, CellulaireAutomaat *cellulaireAutomaat) : Cell(row, col, cellulaireAutomaat){};

    EStates getState() const override;

    void update() override;

    void drawToScreen(MainWindow *window) override;

    std::pair<int, std::string> getPixelArt() override;

    std::vector<bool> getNeighborsRoads();

    /*!
     * geeft alle auto's terug die op de cell staan
     * @return
     */
    std::vector<Vehicle*> getVehicles() const;

    /*!
    * voeg auto toe aan cell
    * @return
    */
    void addVehicle(Vehicle*);

private:
    /*
     * returns rotatie en string van weg
     */
    std::pair<int, std::string> getCorrectRoad(std::vector<bool> &roadConnectPoint);
    std::string pixelArtVervallen = "../PixelArt/Road_Broken.png";
    std::vector<Vehicle*> vehicles;
};

class ResidentialZone : public Cell{
private:
    House building;
public:
    //TODO weg
    ResidentialZone(){
        building = House();
    }

    ResidentialZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat);

    EStates getState() const override;

    void update() override;

    float getHappiness() const override;

    std::pair<int, std::string> getPixelArt() override;
};

class IndustrialZone : public Cell{
private:
    Workplace building;
public:
    //TODO weg
    IndustrialZone(){std::cout << "FOUT" << std::endl;}

    IndustrialZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat);

    EStates getState() const override;

    void update() override;

    float getHappiness() const override;

    std::pair<int, std::string> getPixelArt() override;
};

class StoreZone : public Cell{
private:
    Store building;
public:
    //TODO weg
    StoreZone(){std::cout << "FOUT" << std::endl;}

    StoreZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat);

    EStates getState() const override;

    void update() override;

    float getHappiness() const override;

    std::pair<int, std::string> getPixelArt() override;
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
