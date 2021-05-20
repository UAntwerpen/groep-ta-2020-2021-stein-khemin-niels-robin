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


House::House() {
    bewoners = 4;
    maxPeopleAmount = 8;
    verval = 100;
    setPixelArt("../PixelArt/House.png");
}

Store::Store() {
    setPixelArt("../PixelArt/Store.png");
}

Workplace::Workplace() {
    setPixelArt("../PixelArt/Workplace.png");
}
