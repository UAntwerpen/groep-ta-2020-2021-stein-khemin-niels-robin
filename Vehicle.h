//
// Created by Khemin on 1-5-2021.
//

#ifndef TA_VEHICLE_H
#define TA_VEHICLE_H

#include "Transport.h"
#include <vector>

using namespace std;

class Vehicle : public Transport {
public:

    /**
     * Default constructor
     */
    Vehicle();

    /**
     * Initialiseert een Vehicle op de gegeven loactie en optioneel met een gegeven goal.
     * @param location
     */
    Vehicle(pair<int, int> location, pair<int, int> g = std::make_pair(-1,-1));

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

    /**
     * @brief removePassengers
     */
    void removePassengers();

    /**
    * Verplaatst het Vehicle 1 stap vooruit volgens zijn pad.
    * @param city : De cellulaire automaat waardoor het Vehicle zich beweegt.
    */
    void update(CellulaireAutomaat& city) override;

    EStates getState() const override;

    const string &getPixelart() const;

private:
    vector<Citizen*> people;
    string pixelart;
};

#endif //TA_VEHICLE_H
