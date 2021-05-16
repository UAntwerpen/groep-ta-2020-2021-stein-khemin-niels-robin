//
// Created by Khemin on 9-5-2021.
//

#include "Pathfinding.h"

PFMask::PFMask(CellulaireAutomaat& cellAutomaat, Transport* transport) : width(cellAutomaat.getWidth()), height(cellAutomaat.getHeight()) {
    REQUIRE(1 < width, "Width is too small(must be at least 2)!");
    REQUIRE(1 < height, "Height is too small(must be at least 2)!");
    mask = new PFCell *[(width + 2) * (height + 2)];

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            bool passable;

            if (cellAutomaat(row, col).getState() == ERoad || (cellAutomaat(row, col).getState() == EVegetation && transport->getState() == ECitizen)) {
                passable = true;
            } else {
                passable = false;
            }
            bool goal = transport->getGoal()->getPos() == pair<int, int>(row, col);

            (*this)(row, col) = PFCell(passable, row, col, goal);
        }
    }
}

PFCell& PFMask::operator()(int row, int column) const {
    REQUIRE(0 <= row && row < width, "Row is out of bounds!");
    REQUIRE(0 <= column && column < height, "Column is out of bounds!");
    return *mask[(row + 1) * height + (column + 1)];
}

std::vector<int> PFMask::getNeigbourInts(int row, int col) {
    std::vector<int> ints(4);

    ints[0] = (*this)(row - 1, col).getValue();
    ints[1] = (*this)(row, col + 1).getValue();
    ints[2] = (*this)(row + 1, col).getValue();
    ints[3] = (*this)(row, col - 1).getValue();

    return ints;
}

bool PFMask::update() {
    bool changeMade = false;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            PFCell currCell = (*this)(row, col);

            int min = this->getNeigbourInts(row, col)[0];
            for (int el : this->getNeigbourInts(row, col)) {
                if (el < min) {
                    min = el;
                }
            }

            if (currCell.updatePFCell(min)) {
                changeMade = true;
            }
        }
    }

    return changeMade;
}


