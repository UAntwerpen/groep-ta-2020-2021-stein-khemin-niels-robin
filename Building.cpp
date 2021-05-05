//
// Created by Niels on 5/05/2021.
//

#include "Building.h"
void Building::setPixelArt(string path) {
    pixelart = path;
}


House::House() {
    setPixelArt("PixelArt/House.png");
}

Store::Store() {
    setPixelArt("PixelArt/Store.png");
}

Workplace::Workplace() {
    setPixelArt("PixelArt/Workplace.png");
}
