//
// Created by Khemin on 1-5-2021.
//

#ifndef TA_CITIZEN_H
#define TA_CITIZEN_H

#include "Transport.h"
#include "lib/DesignByContract.h"

class Citizen : public Transport {
public:
    Citizen();

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

private:
    float happiness;
    string pixelart;
};


#endif //TA_CITIZEN_H
