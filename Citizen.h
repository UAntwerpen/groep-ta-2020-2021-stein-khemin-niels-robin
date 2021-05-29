//
// Created by Khemin on 1-5-2021.
//

#ifndef TA_CITIZEN_H
#define TA_CITIZEN_H

#include "Transport.h"
#include "lib/DesignByContract.h"

class Citizen : public Transport {
public:
    /**
     * Default constructor
     */
    Citizen();

    /**
     * Initialiseert een Citizen op de gegeven loactie en optioneel met een gegeven goal.
     * @param location
     */
    Citizen(Cell* location, Cell* g = nullptr);

    /**
     * Geeft de happiness van de Citizen terug adv een float.
     * @return float
     */
    float getHappiness();

    /**
     * Stelt de happiness van de Citizen in op de gegeven waarde.
     * @param h : float : nieuwe happiness waarde
     *
     * ENSURE(this->getHappiness() == h, "setHappiness post condition failure")
     */
    void setHappiness(float h);

    EStates getState() const override;

    const string &getPixelart() const;

    void update(CellulaireAutomaat& city) override;

private:
    float happiness = 0;
    string pixelart;
};


#endif //TA_CITIZEN_H
