//
// Created by Niels on 5/05/2021.
//

#include "Building.h"
void Building::setPixelArt(std::string path) {
    pixelart = path;
}

int Building::getVerval() {
    return verval;
}

std::string Building::getPixelArt() {
    return this->pixelart;
}

std::string Building::getExpiredPixelArt() {
    return this->pixelart.substr(0, this->pixelart.size()-4) + "_Broken.png";
}

House::House() {
    bewoners = 4;
    maxPeopleAmount = 8;
    verval = 100;
    setPixelArt("../PixelArt/House.png");
}

void House::addResident(Citizen *resident) {

}

void House::removeResident(Citizen *resident) {

}

Store::Store() {
    setPixelArt("../PixelArt/Store.png");
}

Workplace::Workplace() {
    setPixelArt("../PixelArt/Workplace.png");
}
