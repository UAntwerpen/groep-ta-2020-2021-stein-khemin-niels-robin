
#include "lib/DesignByContract.h"
#include "CellulaireAutomaat.h"

CellulaireAutomaat::CellulaireAutomaat(int width, int height) : width(width), height(height) {
    REQUIRE(1 < width, "Width is too small(must be at least 2)!");
    REQUIRE(1 < height, "Height is too small(must be at least 2)!");
    matrix = new Cell *[(width + 2) * (height + 2)];
}


Cell &CellulaireAutomaat::operator()(int row, int column) {
    REQUIRE(0 <= row && row < width, "Row is out of bounds!");
    REQUIRE(0 <= column && column < height, "Column is out of bounds!");
    return *matrix[(row + 1) * height + (column + 1)];
}

std::vector<Cell *> CellulaireAutomaat::getNeighbourhood(int row, int col) {
    REQUIRE(0 <= row && row < width, "Row is out of bounds!");
    REQUIRE(0 <= col && col < height, "Column is out of bounds!");
    std::vector<Cell *> neighbourhood(8);
    neighbourhood[0] = &(*this)(row - 1, col - 1);
    neighbourhood[1] = &(*this)(row - 1, col);
    neighbourhood[2] = &(*this)(row - 1, col + 1);
    neighbourhood[3] = &(*this)(row, col + 1);
    neighbourhood[4] = &(*this)(row + 1, col + 1);
    neighbourhood[5] = &(*this)(row + 1, col);
    neighbourhood[6] = &(*this)(row + 1, col - 1);
    neighbourhood[7] = &(*this)(row, col - 1);
    return neighbourhood;
}

int CellulaireAutomaat::getNeighbourhoodValue(int row, int col) {
    REQUIRE(0 <= row && row < width, "Row is out of bounds!");
    REQUIRE(0 <= col && col < height, "Column is out of bounds!");
    int value = 0;
    static int powers[8] = {static_cast<int>(pow(5, 7)), static_cast<int>(pow(5, 6)), static_cast<int>(pow(5, 5)),
                            static_cast<int>(pow(5, 4)), static_cast<int>(pow(5, 3)),
                            static_cast<int>(pow(5, 2)), 5, 1};

    value += ((*this)(row - 1, col - 1)).getState() * powers[0];
    value += ((*this)(row - 1, col)).getState() * powers[1];
    value += ((*this)(row - 1, col + 1)).getState() * powers[2];
    value += ((*this)(row, col + 1)).getState() * powers[3];
    value += ((*this)(row + 1, col + 1)).getState() * powers[4];
    value += ((*this)(row + 1, col)).getState() * powers[5];
    value += ((*this)(row + 1, col - 1)).getState() * powers[6];
    value += ((*this)(row, col - 1)).getState() * powers[7];
    return value;
}

void CellulaireAutomaat::changeCell(int row, int column, Cell *to) {
    REQUIRE(0 <= row && row < width, "Row is out of bounds!");
    REQUIRE(0 <= column && column < height, "Column is out of bounds!");
    REQUIRE(to != nullptr, "De gegeven cell is een nullptr!");
    delete matrix[row * height + column];
    matrix[row * height + column] = to;
}

void CellulaireAutomaat::update() {

}
