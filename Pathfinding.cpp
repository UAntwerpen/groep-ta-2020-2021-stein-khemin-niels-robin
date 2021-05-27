//
// Created by Khemin on 9-5-2021.
//

#include "Pathfinding.h"

PFMask::PFMask(int width, int height) : width(width), height(height) {
    REQUIRE(1 < width, "Width is too small(must be at least 2)!");
    REQUIRE(1 < height, "Height is too small(must be at least 2)!");
    mask = new PFCell*[height];
    for (int i = 0; i < height; i++){
        mask[i] = new PFCell[width];
    }

    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            mask[row][col] = PFCell(false, row, col, false);
        }
    }
}

PFMask::PFMask(CellulaireAutomaat& cellAutomaat, Cell* goal, bool isCar) : width(cellAutomaat.getWidth()), height(cellAutomaat.getHeight()) {
    REQUIRE(1 < width, "Width is too small(must be at least 2)!");
    REQUIRE(1 < height, "Height is too small(must be at least 2)!");
    REQUIRE(goal != nullptr, "Mask must have a non nullptr goal.");

    mask = new PFCell *[height];
    for (int i = 0; i < height; i++){
        mask[i] = new PFCell[width];
    }

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            bool passable;

            if (cellAutomaat(row, col)->getState() == ERoad ||
                (cellAutomaat(row, col)->getState() == EVegetation && !isCar) ||
                    goal->getPos() == std::pair<int, int>(row, col)) {
                passable = true;
            } else {
                passable = false;
            }
            bool isGoal = goal->getPos() == std::pair<int, int>(row, col);

            this->getCell(row, col) = PFCell(passable, row, col, isGoal);
        }
    }
}

int PFMask::getWidth() const {
    return width;
}

int PFMask::getHeight() const {
    return height;
}

PFCell &PFMask::getCell(int row, int col) {
    REQUIRE(0 <= row && row < width, "Row is out of bounds!");
    REQUIRE(0 <= col && col < height, "Column is out of bounds!");
    return mask[row][col];
}

std::vector<int> PFMask::getNeighbourInts(int row, int col) {
    std::vector<int> ints;

    if (row - 1 >= 0){
        ints.push_back(this->getCell(row - 1, col).getValue());
    }

    if (col + 1 < this->getWidth()){
        ints.push_back(this->getCell(row, col + 1).getValue());
    }

    if (row + 1 < this->getHeight()) {
        ints.push_back(this->getCell(row + 1, col).getValue());
    }

    if (col - 1 >= 0) {
        ints.push_back(this->getCell(row, col - 1).getValue());
    }


    return ints;
}

std::vector<PFCell *> PFMask::getNeighbours(int row, int col) {
    std::vector<PFCell*> neighbours;

    if (row - 1 >= 0){
        neighbours.push_back(&this->getCell(row - 1, col));
    }

    if (col + 1 < this->getWidth()){
        neighbours.push_back(&this->getCell(row, col + 1));
    }

    if (row + 1 < this->getHeight()) {
        neighbours.push_back(&this->getCell(row + 1, col));
    }

    if (col - 1 >= 0) {
        neighbours.push_back(&this->getCell(row, col - 1));
    }

    return neighbours;
}

bool PFMask::update() {
    bool changeMade = false;
    PFMask copy = *this;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            PFCell* currCell = &this->getCell(row, col);

            int min = copy.getNeighbourInts(row, col)[0];
            for (int el : copy.getNeighbourInts(row, col)) {
                if (el < min) {
                    min = el;
                }
            }

            if (currCell->updatePFCell(min)) {
                changeMade = true;
            }
        }
    }

    return changeMade;
}

void PFMask::generateMask() {
    while (update()) {
        // ** Does nothing here ** //
    }
}
