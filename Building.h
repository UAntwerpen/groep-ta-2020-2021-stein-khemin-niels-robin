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
    /*!
     * zet en pixel art op het gebouw
     */
    void setPixelArt(std::string path);

    /*!
     * geeft de pixel art terug
     */
    std::string getPixelArt();

    /*!
     * geeft de vervallen pixel art terug
     */
    std::string getExpiredPixelArt();

    /*!
     * geeft het aantal dagen tot verval terug
     */
    int getVerval();

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
