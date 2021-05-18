//
// Created by Khemin on 1-5-2021.
//

#ifndef TA_VEHICLE_H
#define TA_VEHICLE_H

#include "Transport.h"
#include <vector>

class Citizen;

class Vehicle : public Transport {
public:
    /**
     * Geeft personen in het Vehicle terug.
     * @return vector van Citizen class pointers
     */
    vector<Citizen*> getPeople();

    /**
     * Stelt de personen in het Vehicle gelijk aan de gegeven vector.
     * @param pass : nieuwe passagiers van het Vehicle.
     */
    void setPeople(vector<Citizen*> pass);

    /**
     * Geeft een persoon in de auto terug adv de gegeven index.
     * @param index : unsigned integer
     * @return Citizen class pointer
     */
    Citizen* operator[](unsigned int index);

    /**
     * Voegt een persoon toe in het Vehicle.
     * @param person : persoon die aan het Vehicle wordt toegevoegd
     */
    void addPerson(Citizen* person);

    EStates getState() const override;

private:
    vector<Citizen*> people;
};


#endif //TA_VEHICLE_H
