//
// Created by Niels on 5/05/2021.
//

#ifndef TA_BUILDING_H
#define TA_BUILDING_H

#include <string>

class Building {
public:
    void setPixelArt(std::string path);

protected:
    int bewoners;
    int maxPeopleAmount;
    int verval;
    std::string pixelart;
};


class House : public Building{
public:
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
