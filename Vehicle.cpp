//
// Created by Khemin on 1-5-2021.
//

#include "Vehicle.h"

Vehicle::Vehicle(){
    string pixArt = "Car";
    int random = (rand()%3)+1;
    pixArt = pixArt + to_string(random) + ".png";
    pixelart = pixArt;
}

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

EStates Vehicle::getState() const {
    return EVehicle;
}

const string &Vehicle::getPixelart() const {
    return pixelart;
}
