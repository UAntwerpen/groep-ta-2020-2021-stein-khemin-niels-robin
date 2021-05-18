//
// Created by Niels on 5/05/2021.
//

#include "Building.h"
void Building::setPixelArt(std::string path) {
    pixelart = path;
}


House::House() {
    this->bewoners = 4;
    this->maxPeopleAmount = 8;
    this->verval = 100;
    setPixelArt("../PixelArt/House.png");
}

Store::Store() {
    setPixelArt("../PixelArt/Store.png");
}

Workplace::Workplace() {
    setPixelArt("../PixelArt/Workplace.png");
}
