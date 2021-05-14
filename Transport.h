//
// Created by Khemin on 1-5-2021.
//

#ifndef TA_TRANSPORT_H
#define TA_TRANSPORT_H

#include <string>
#include "CellulaireAutomaat.h"

using namespace std;

class Cell;
class CellulaireAutomaat;

class Transport {
public:
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
     * Verplaatst het Transport in de gegeven richting;
     * @param direction : richting waarin het Transport beweegt
     */
    void update(CellulaireAutomaat& city, char direction);

private:
    // not owner of cell, Don't delete!
    Cell* location;

    Cell* goal;
    string route;

    int speed;
};


#endif //TA_TRANSPORT_H
