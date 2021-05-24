//
// Created by Niels on 5/05/2021.
//

#ifndef TA_BUILDING_H
#define TA_BUILDING_H

#include <string>
#include <vector>

class Citizen;

class Building {
public:
    void setPixelArt(std::string path);
    std::string getPixelArt();
    std::string getExpiredPixelArt();
    int getVerval();

protected:
    int bewoners;
    int maxPeopleAmount;
    int verval;
    std::string pixelart;
    std::vector<Citizen*> residents;
};

class House : public Building{
public:
    void addResident(Citizen* resident);
    void removeResident(Citizen* resident);
    House();
};

class Store : public Building{
public:
    Store();
};

class Workplace : public Building{
public:
    Workplace();
};

#endif //TA_BUILDING_H
