//
// Created by Khemin on 1-5-2021.
//

#include "Transport.h"
#include "lib/DesignByContract.h"

Cell *Transport::getLocation() {
    return location;
}

void Transport::setLocation(Cell *cell) {
    location = cell;
    ENSURE(this->getLocation() == cell, "location not set to given value (post condition failure)");
}

