
#include "lib/DesignByContract.h"
#include "CellulaireAutomaat.h"

CellulaireAutomaat::CellulaireAutomaat(int width, int height): width(width), height(height) {
    REQUIRE(1 < width, "Width is too small(must be at least 2)!");
    REQUIRE(1 < height, "Height is too small(must be at least 2)!");
    matrix = new Cell[width*height];
}


Cell& CellulaireAutomaat::operator()(int row, int column) {
    REQUIRE(0 <= row && row < width, "Row is out of bounds!");
    REQUIRE(0 <= column && column < height, "Column is out of bounds!");
    return matrix[row * height + column];
}

std::vector<Cell *> CellulaireAutomaat::getNeighbourhood(int row, int col) {
    std::vector<Cell*> neighbourhood(8);
    neighbourhood[0] = &(*this)(row - 1, col - 1);
    neighbourhood[0] = &(*this)(row - 1, col);
    neighbourhood[0] = &(*this)(row - 1, col + 1);
    neighbourhood[0] = &(*this)(row, col + 1);
    neighbourhood[0] = &(*this)(row + 1, col + 1);
    neighbourhood[0] = &(*this)(row + 1, col);
    neighbourhood[0] = &(*this)(row + 1, col - 1);
    neighbourhood[0] = &(*this)(row, col - 1);
    return neighbourhood;
}
