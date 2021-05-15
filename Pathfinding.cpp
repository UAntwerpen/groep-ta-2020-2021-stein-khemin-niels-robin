//
// Created by Khemin on 9-5-2021.
//

#include "Pathfinding.h"

PFMask::PFMask(CellulaireAutomaat& cellAutomaat, Transport* transport) : width(cellAutomaat.getWidth()), height(cellAutomaat.getHeight()) {
    REQUIRE(1 < width, "Width is too small(must be at least 2)!");
    REQUIRE(1 < height, "Height is too small(must be at least 2)!");
    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            bool passable;

            if (cellAutomaat(row, col).getState() == ERoad || (cellAutomaat(row, col).getState() == EVegetation && transport->getState() == ECitizen)) {
                passable = true;
            } else {
                passable = false;
            }
        }
    }
}

std::vector<int> PFMask::getNeigbourInts(int row, int col) {


}

bool PFMask::update() {
    return false;
}
