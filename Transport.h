//
// Created by Khemin on 1-5-2021.
//

#ifndef TA_TRANSPORT_H
#define TA_TRANSPORT_H

#include <string>
#include "CellulaireAutomaat.h"
#include "Lib.h"
class pathFinding;
class PFMask;

using namespace std;

class Transport {
public:
    /**
     * Default Constructor
     */
    Transport();

    virtual ~Transport();

    /**
     * Initialiseert een Transport object met gegeven locatie en optioneel een gegeven goal.
     * @param location : Cell pointer : Locatie waar transport geinitialiseerd wordt.
     * @param goal : Cell pointer : De goal van het transport. Het transport zal naar deze cel verplaatsen met het Pathfinding algoritme.
     */
    Transport(Cell* location, Cell* goal = nullptr);

    /**
     * Geeft een pointer terug naar de huidige locatie van het Transport.
     *
     * @return Pointer naar de Cell die het Transport bevat.
     */
    Cell* getLocation();

    /**
     * Zet het location attribuut van het Transport gelijk aan de gegeven waarde.
     *
     * @param cell : nieuwe location van het transport
     *
     * ENSURE(this->getLocation() == cell, "setLoaction post condition failure")
     */
    void setLocation(Cell* cell);

    /**
     * Geeft een pointer terug naar de bestemming van het Transport.
     *
     * @return Cell Pointer naar bestemming van het Transport.
     */
    Cell* getGoal();

    /**
     * Stelt een nieuwe bestemming in voor het Transport.
     *
     * @param cell : nieuwe bestemming van het transport
     *
     * ENSURE(this->getGoal() == cell, "setGoal post condition failure")
     */
    void setGoal(Cell* cell);

    /**
     * Geeft de status van het voertuig terug.
     * @return true als het voertuig onderweg is, anders false.
     */
    bool getStatus();

    /**
     * Stelt een nieuwe status in voor het voertuig.
     *
     * @param status : bool : nieuwe status van het voertuig. (true = onderweg, false = op bestemming)
     *
     * ENSURE(this->getStatus() == status, "setStatus post condition failure")
     */
    void setStatus(bool status);

    /**
     * Geeft de PFMask van het Transport terug.
     *
     * @return PFMask class pointer
     */
    PFMask* getMask();

    /**
     * Stelt een nieuw PFMask in.
     *
     * @param m : nieuwe PFMask voor het Transport.
     */
    void setMask(PFMask* m);

    /**
     * Geeft de huidige route van het Transport terug.
     * @return string
     */
    string getRoute();

    /**
     * Stelt een nieuwe route in voor het Transport.
     * @param r : string : nieuwe route voor het Transport
     */
    void setRoute(string r);

    /**
     * Berekent de route voor het Transport adv het gegeven PFMask.
     * @param mask : Pathfinding mask om de route mee te berekenen.
     *
     * @pre Transport must have a corresponding PFMask before calling calculateRoute.
     * REQUIRE(mask.getCell(goalPoss.first, goalPoss.second).getValue() == 0, "incompatible PFMask for this Transport.")
     */
    void calculateRoute();

    /**
     * Geeft de huidige progress doorheen de route terug.
     * @return integer : index van de route string waar het transport zich momenteel bevindt.
     */
    int getProgress() const;

    /**
     * Stelt de progress van het transport in op de gegeven index.
     * @param i : integer : nieuwe progress index van het Transport.
     *
     * ENSURE(this->getProgress() == i, "setProgress post condition failure")
     */
    void setProgress(int i);

    /**
     * Verhoogt de progress van het Transport met 1.
     */
    void increaseProgress();

    /**
     * Geeft de huidige richting van het Transport terug.
     * @return : character : Richting waarin het Transport momenteel beweegt.
     */
    char getDirection() const;

    /**
     * Stelt de richting van het Transport in op het gegeven character.
     * @param c : character : nieuwe richting van het Transport.
     *
     * ENSURE(this->getDirection() == c, "setDirection post condition failure")
     */
    void setDirection(char c);

    /**
     * Verandert de richting van het Transport adv de volgende stap die het Transport zet.
     *
     * REQUIRE(not this->getRoute().empty(), "Route is empty when calling changeDirection")
     * ENSURE(this->getDirection() == this->getRoute()[next], "chanceDirection did not change direction correctly.")
     */
    void changeDirection();

    /**
    * Geeft de thuislocatie van het voertuig terug.
    * @return Cell class pointer
    */
    Cell* getHome();

    /**
     * Geeft de coordinaten terug van de cel waarnaar het transport zijn volgende stap zal zetten.
     * @return pair of integers (row, col)
     */
    pair<int, int> getNextStep();

    /**
     * Verplaatst het Transport 1 stap vooruit volgens zijn pad.
     * @param city : De cellulaire automaat waardoor het Tranport zich beweegt.
     */
    virtual void update(CellulaireAutomaat& city) = 0;

    /*!
     * geeft de gepaste enum waarde terug
     * @return enum waarde
     */
    virtual EStates getState() const = 0;

private:
    // not owner of cell, Don't delete!
    Cell* location;

    Cell* goal;
    bool inTransit;
    PFMask* mask;
    string route;

    int progress;
    char direction;

    Cell* home;

//    int speed;
};


#endif //TA_TRANSPORT_H
