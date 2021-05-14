//
// Created by Khemin on 1-5-2021.
//

#include "Vehicle.h"

void Vehicle::setPeople(vector<Citizen *> pass) {

}

vector<Citizen *> Vehicle::getPeople() {
    return vector<Citizen *>();
}

Citizen *Vehicle::operator[](unsigned int ind) {
    return people[ind];
}

void Vehicle::addPerson(Citizen *person) {
    people.push_back(person);
}
