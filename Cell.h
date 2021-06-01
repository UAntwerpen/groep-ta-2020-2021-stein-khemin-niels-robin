

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
class CellulaireAutomaat;

class Cell {
public:
    /*!
     * copy contructor
     * @param p2: cell om te kopieren
     */
    Cell(const Cell &p2);

    /*!
     * contructor voor cell
     * @param row: rij van de cell
     * @param col: col van de cell
     * @param cellulaireAutomaat: de cellulaireAutomaat waar de cell een deel van uitmaakt
     */
    Cell(int row, int col, CellulaireAutomaat* cellulaireAutomaat);

    /*!
     * desctructor cell
     */
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
     * geeft terug hoeveel happiness een bepaalde cell uitstoot (tussen -1 en 1)
     * @return float
     */
    virtual float getHappiness() const {return 0;};

    /*!
     * Geeft voor elke zijde weer of er een weg aan verbonden kan worden;
     *  [0]: boven        [0]
     *  [1]: links      xxxxx
     *  [2]: onder  [3]  xxxxx  [1]
     *  [3]: rechts       xxxxx
     *                    [2]
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

    /*!
     * functie dat true terug geeft indien de grond in verval is geraakt
     * @return true/false : vervallen/niet vervalen
     */
    bool isExpired();

    /*!
     * functie die het beste alternatief geeft voor de huidige cell locatie
     * @return best cell alternatief
     */
    Cell* bestAlternativeCell();

    /*!
     * Controleert of huidige cell is verbonden met de weg op locatie row, col
     * @param row: rij van cell om te controleren
     * @param col: col van cell om te controleren
     * @param roads: wegen die al gecontroleerd zijn
     * @param main: is de eerste road om te controleren
     * @return
     */
    bool isConnectedTo(int row, int col,  std::vector<std::pair<int,int>>* roads = nullptr, bool main = true);

    /*!
     * geeft in een vetor weer welke cellen er wegen zijn
     *  [0]: boven        [0]
     *  [1]: links      xxxxx
     *  [2]: onder  [3]  xxxxx  [1]
     *  [3]: rechts       xxxxx
     *                    [2]
     * @return vector volgens bovenstaande indeling
     */
    std::vector<bool> getNeighborsRoads();

    /*!
     * geeft pixel art terug
     * @return int: rotation, string: pad to pixel art
     */
    virtual std::pair<int, std::string> getPixelArt(){return std::pair<int, std::string>(0, "../PixelArt/Default.png");};

    /*!
     * geeft auto op cel terug
     * @return pointer to car
     */
    virtual Vehicle* getCar();

    /*!
     * zet auto op cell
     */
    virtual void setCar(Vehicle* vehicle);

protected:
    int row = 0;
    int col = 0;
    double daysUntilExpired = 0;

    CellulaireAutomaat* cellulaireAutomaat;
    std::vector<Citizen*> people;
    virtual void updateDaysUntilExpired();
};

class Vegetation : public Cell{
public:
    /*!
     * constructor Vegetation
     * @param row: rij van de cell
     * @param col: col van de cell
     * @param cellulaireAutomaat: de cellulaireAutomaat waar de cell een deel van uitmaakt
     */
    Vegetation(int row, int col, CellulaireAutomaat* cellulaireAutomaat): Cell(row, col, cellulaireAutomaat) {  }

    /*!
    * copy contructor
    * @param p2: cell om te kopieren
    */
    Vegetation(const Cell &p2);

    /*!
     * geeft Estate van soort cell terug
     * @return
     */
    EStates getState() const override;

    /*!
     * update de cell
     */
    void update() override;

    /*!
     * geeft pixel art terug
     * @return int: rotation, string: pad to pixel art
     */
    std::pair<int, std::string> getPixelArt() override;

    /*!
     * geeft terug hoeveel happiness een bepaalde cell uitstoot (tussen -1 en 1)
     * @return float
     */
    float getHappiness()  const override;
private:
    std::string pixelArt = "../PixelArt/Park.png";
    std::string pixelArtVervallen = "../PixelArt/Park_Broken.png";
};

class Road : public Cell{
public:
    /*!
    * copy contructor
    * @param p2: cell om te kopieren
    */
    Road(const Cell &p2);

    /*!
     * constructor Vegetation
     * @param row: rij van de cell
     * @param col: col van de cell
     * @param cellulaireAutomaat: de cellulaireAutomaat waar de cell een deel van uitmaakt
     */
    Road(int row, int col, CellulaireAutomaat *cellulaireAutomaat) : Cell(row, col, cellulaireAutomaat){};

    /*!
     * geeft Estate van soort cell terug
     * @return
     */
    EStates getState() const override;

    /*!
     * update de cell
     */
    void update() override;

    /*!
    * geeft pixel art terug
    * @return int: rotation, string: pad to pixel art
    */
    std::pair<int, std::string> getPixelArt() override;

    /*!
     * geeft terug hoeveel happiness een bepaalde cell terug
     * @return float
     */
    float getHappiness() const override;

    /*!
     * voeg auto toe aan cell
     * @return
     */
    void addVehicle(Vehicle*);

    /*!
     * update het aantal dagen tot verval
     */
    void updateDaysUntilExpired() override;

private:
    /*!
     * geeft corecte pixel art van road terug
     * @param roadConnectPoint: vector volgend formaat:
     *  [0]: boven        [0]
     *  [1]: links      xxxxx
     *  [2]: onder  [3]  xxxxx  [1]
     *  [3]: rechts       xxxxx
     *                    [2]
     * @return int: rotatie pixel art, pad naar pixel art
     */
    std::pair<int, std::string> getCorrectRoad(std::vector<bool> &roadConnectPoint);
    std::string pixelArtVervallen = "../PixelArt/Road_Broken.png";
    std::vector<Vehicle*> vehicles;
    std::vector<Citizen*> citizen;
};

class ResidentialZone : public Cell{
private:
    House building;
    Vehicle* car = nullptr;
public:
    /*!
     * desctructor cell
     */
    ~ResidentialZone();

    /*!
    * copy contructor
    * @param p2: cell om te kopieren
    */
    ResidentialZone(const Cell &p2);

    /*!
     * contructor voor cell
     * @param row: rij van de cell
     * @param col: col van de cell
     * @param cellulaireAutomaat: de cellulaireAutomaat waar de cell een deel van uitmaakt
     */
    ResidentialZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat);

    /*!
     * geeft Estate van soort cell terug
     * @return
     */
    EStates getState() const override;

    /*!
     * update de cell
     */
    void update() override;

    /*!
     * geeft terug hoeveel happiness een bepaalde cell terug
     * @return float
     */
    float getHappiness() const override;

    /*!
     * geeft pixel art terug
     * @return int: rotation, string: pad to pixel art
     */
    std::pair<int, std::string> getPixelArt() override;

    /*!
     * geeft auto op cel terug
     * @return pointer to car
     */
    Vehicle* getCar() override;

    /*!
     * zet auto op cell
     * @param vehicle
     */
    void setCar(Vehicle* vehicle) override;
};

class IndustrialZone : public Cell{
private:
    Workplace building;
public:
    /*!
    * copy contructor
    * @param p2: cell om te kopieren
    */
    IndustrialZone(const Cell &p2);

    /*!
     * contructor voor cell
     * @param row: rij van de cell
     * @param col: col van de cell
     * @param cellulaireAutomaat: de cellulaireAutomaat waar de cell een deel van uitmaakt
     */
    IndustrialZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat);

    /*!
     * geeft Estate van soort cell terug
     * @return
     */
    EStates getState() const override;

    /*!
     * update de cell
     */
    void update() override;

    /*!
    * geeft terug hoeveel happiness een bepaalde cell terug
    * @return float
    */
    float getHappiness() const override;

    /*!
     * geeft pixel art terug
     * @return int: rotation, string: pad to pixel art
     */
    std::pair<int, std::string> getPixelArt() override;
};

class StoreZone : public Cell{
private:
    Store building;
public:
    /*!
    * copy contructor
    * @param p2: cell om te kopieren
    */
    StoreZone(const Cell &p2);

    /*!
     * contructor voor cell
     * @param row: rij van de cell
     * @param col: col van de cell
     * @param cellulaireAutomaat: de cellulaireAutomaat waar de cell een deel van uitmaakt
     */
    StoreZone(int row, int col, CellulaireAutomaat *cellulaireAutomaat);

    /*!
     * geeft Estate van soort cell terug
     * @return
     */
    EStates getState() const override;

    /*!
     * update de cell
     */
    void update() override;

    /*!
     * geeft terug hoeveel happiness een bepaalde cell terug
     * @return float
     */
    float getHappiness() const override;

    /*!
     * geeft pixel art terug
     * @return int: rotation, string: pad to pixel art
     */
    std::pair<int, std::string> getPixelArt() override;
};

#endif //TA_CELL_H
