#include <algorithm>

#include "lib/DesignByContract.h"
#include "CellulaireAutomaat.h"
#include "Lib.h"
#include "Cell.h"

CellulaireAutomaat::CellulaireAutomaat(int width, int height, const std::string& rules, bool save_rules) : width(width), height(height), rules(rules) {
    REQUIRE(1 < width, "Width is too small(must be at least 2)!");
    REQUIRE(1 < height, "Height is too small(must be at least 2)!");
    matrix.resize(width * height);
    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            changeCell(row, col, new Vegetation(row, col, this));
        }
    }

    if (save_rules) {
        const void *address = static_cast<const void *>(this);
        std::stringstream ss;
        ss << address;
        std::string name = ss.str();
        std::ofstream file(name + ".txt", std::ofstream::trunc|std::ofstream::binary);
        if (file.is_open()) {
            file << rules;
        } else {
            std::cerr << "couldn't open file!" << std::endl;
        }
        file.close();
    }
}

CellulaireAutomaat::CellulaireAutomaat(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    bool map = false;
    int row = 0;
    while(file.good()) {
        std::getline(file, line);
        if (line.find("DIM=") != std::string::npos){
            size_t xpos = line.find('x');
            int wi = std::stoi(line.substr(4, xpos - 4));
            int he = std::stoi(line.substr(7, line.length()));
            width = wi;
            height = he;
            matrix = std::vector<Cell*>(width * height);
        }
        else if(line.find("MAP:") != std::string::npos){
            map = true;
        }
        else if (map){
            int col = 0;
            for (char c: line){
                switch (c) {
                    case 'r':
                        changeCell(row, col, new Road(row, col, this));
                        break;
                    case 'R':
                        changeCell(row, col, new ResidentialZone(row, col, this));
                        break;
                    case 'I':
                        changeCell(row, col, new IndustrialZone(row, col, this));
                        break;
                    case 'S':
                        changeCell(row, col, new StoreZone(row, col, this));
                        break;
                    case 'V':
                    default:
                        changeCell(row, col, new Vegetation(row, col, this));
                        break;
                }
                ++col;
            }
            ++row;
        }
        if (line.empty()){
            break;
        }
        std::cout << line << std::endl;
    }

    file.close();
}

CellulaireAutomaat::~CellulaireAutomaat() {
    for (const auto& cell: matrix)
        delete cell;
}

Cell* CellulaireAutomaat::operator()(int row, int column) const {
    REQUIRE(0 <= row && row < height, "Row is out of bounds!");
    REQUIRE(0 <= column && column < width, "Column is out of bounds!");
    Cell* ret = matrix[row * width + column];
    ENSURE(ret != nullptr, "returned cell is a nullptr!");
    return ret;
}

std::vector<Cell *> CellulaireAutomaat::getNeighbourhood(int row, int col) const {
    REQUIRE(0 <= row && row < height, "Row is out of bounds!");
    REQUIRE(0 <= col && col < width, "Column is out of bounds!");
    std::vector<Cell *> neighbourhood(8);

    neighbourhood[0] = 0 <= row - 1 && 0 <= col - 1 ? (*this)(row - 1, col - 1) : nullptr;
    neighbourhood[1] = 0 <= row - 1 ? (*this)(row - 1, col) : nullptr;
    neighbourhood[2] = 0 <= row - 1 && col + 1 < width ? (*this)(row - 1, col + 1) : nullptr;
    neighbourhood[3] = col + 1 < width ? (*this)(row, col + 1) : nullptr;
    neighbourhood[4] = row + 1 < height && col + 1 < width ? (*this)(row + 1, col + 1) : nullptr;
    neighbourhood[5] = row + 1 < height ? (*this)(row + 1, col) : nullptr;
    neighbourhood[6] = row + 1 < height && 0 <= col - 1 ? (*this)(row + 1, col - 1) : nullptr;
    neighbourhood[7] = 0 <= col - 1 ? (*this)(row, col - 1) : nullptr;
    return neighbourhood;
}

int CellulaireAutomaat::getNeighbourhoodValue(int row, int col) {
    REQUIRE(0 <= row && row < height, "Row is out of bounds!");
    REQUIRE(0 <= col && col < width, "Column is out of bounds!");
    int value = 0;
    static int powers[8] = {static_cast<int>(pow(5, 7)), static_cast<int>(pow(5, 6)), static_cast<int>(pow(5, 5)),
                            static_cast<int>(pow(5, 4)), static_cast<int>(pow(5, 3)),
                            static_cast<int>(pow(5, 2)), 5, 1};
    if (0 <= row - 1 && 0 <= col - 1)
        value += ((*this)(row - 1, col - 1))->getState() * powers[0];
    if (0 <= row - 1)
        value += ((*this)(row - 1, col))->getState() * powers[1];
    if (0 <= row - 1 && col + 1 < width)
        value += ((*this)(row - 1, col + 1))->getState() * powers[2];
    if (col + 1 < width)
        value += ((*this)(row, col + 1))->getState() * powers[3];
    if (row + 1 < height && col + 1 < width)
        value += ((*this)(row + 1, col + 1))->getState() * powers[4];
    if (row + 1 < height)
        value += ((*this)(row + 1, col))->getState() * powers[5];
    if (row + 1 < height && 0 <= col - 1)
        value += ((*this)(row + 1, col - 1))->getState() * powers[6];
    if (0 <= col - 1)
        value += ((*this)(row, col - 1))->getState() * powers[7];
    return value;
}

int CellulaireAutomaat::getNeighbourhoodValue(int row, int col, const std::vector<std::vector<EStates>>& map) {
    REQUIRE(0 <= row && row < (int)map.size(), "Row is out of bounds!");
    REQUIRE(0 <= col, "Column is out of bounds!");
    for (const auto & c : map) {
        REQUIRE(col < (int)c.size(), "Column is out of bounds!");
    }
    int value = 0;
    const static int powers[8] = {static_cast<int>(pow(5, 7)), static_cast<int>(pow(5, 6)), static_cast<int>(pow(5, 5)),
                            static_cast<int>(pow(5, 4)), static_cast<int>(pow(5, 3)),
                            static_cast<int>(pow(5, 2)), 5, 1};
    if (0 <= row - 1 && 0 <= col - 1)
        value += map[row - 1][col - 1] * powers[0];
    if (0 <= row - 1)
        value += map[row - 1][col] * powers[1];
    if (0 <= row - 1 && col + 1 < (int)map[0].size())
        value += map[row - 1][col + 1] * powers[2];
    if (col + 1 < (int)map[0].size())
        value += map[row][col + 1] * powers[3];
    if (row + 1 < (int)map.size() && col + 1 < (int)map[0].size())
        value += map[row + 1][col + 1] * powers[4];
    if (row + 1 < (int)map.size())
        value += map[row + 1][col] * powers[5];
    if (row + 1 < (int)map.size() && 0 <= col - 1)
        value += map[row + 1][col - 1] * powers[6];
    if (0 <= col - 1)
        value += map[row][col - 1] * powers[7];
    return value;
}

void CellulaireAutomaat::changeCell(int row, int column, Cell *to) {
    REQUIRE(0 <= row && row < height, "Row is out of bounds!");
    REQUIRE(0 <= column && column < width, "Column is out of bounds!");
    REQUIRE(to != nullptr, "De gegeven cell is een nullptr!");
    delete matrix[row * width + column];
    matrix[row * width + column] = to;
    ENSURE((*this)(row, column) == to, "Error changing the cell!");
}

void CellulaireAutomaat::updateRules() {
    std::vector<std::pair<int, int>> old_branches = branches;
    branches.clear();
    for (const auto& pos: old_branches) {
        updateRulesHelper(pos.first, pos.second);
    }
}

void CellulaireAutomaat::updateCells(bool noExpire) {
    for (int col = 0; col < width; col++) {
        for (int row = 0; row < height; row++) {
            if (!(*this)(row, col)->isConnectedTo(main_street.first, main_street.second) ){
                changeCell(row, col, new Vegetation(*(*this)(row, col)));
            }

            if((*this)(row, col)->isExpired() && !noExpire){
                Cell* newZone = (*this)(row, col)->bestAlternativeCell();
                changeCell(row, col, newZone);

                std::vector<Cell *>neighbourhood = this->getNeighbourhood(newZone->getPos().first, newZone->getPos().second);
                for(auto it = neighbourhood.begin(); it != neighbourhood.end(); it++){
                    if((*it) != nullptr){
                        if(!(*it)->isConnectedTo(main_street.first, main_street.second)){
                            Cell* createRoad = new Road(*(*this)(row, col));
                            changeCell(row, col, createRoad);
                        }
                    }
                }
            }
            (*this)(row, col)->update();
        }
    }
}

int CellulaireAutomaat::count(const EStates &state) const {
    int counter = 0;
    for (int col = 0; col < width; col++) {
        for (int row = 0; row < height; row++) {
            if ((*this)(row, col)->getState() == state) {
                counter++;
            }
        }
    }
    return counter;
}

int CellulaireAutomaat::count(const EStates &state, int row, int col, int radius) const {
    int counter = 0;
    for (int c = col-radius; c <= col+radius; c++){
        for (int r = row-radius; r <= row+radius; r++){
            if(r >= 0 && r < width && c >= 0 && c < height && (*this)(r, c)->getState() == state){
                    counter++;
            }
        }
    }
    return counter;
}

std::map<EStates, int> CellulaireAutomaat::count_all() const {
    std::map<EStates, int> counters;
    counters[static_cast<EStates>(0)] = 0;
    counters[static_cast<EStates>(1)] = 0;
    counters[static_cast<EStates>(2)] = 0;
    counters[static_cast<EStates>(3)] = 0;
    counters[static_cast<EStates>(4)] = 0;
    for (int col = 0; col < width; col++){
        for (int row = 0; row < height; row++){
            EStates cell_state = (*this)(row, col)->getState();
            counters[cell_state]++;
        }
    }
    return counters;
}

    int CellulaireAutomaat::getWidth() const {
        ENSURE(width > 0, "Width is less then 0!");
        return width;
    }

    int CellulaireAutomaat::getHeight() const {
        ENSURE(height > 0, "Height is less then 0!");
        return height;
    }

void CellulaireAutomaat::addMainStreet(int row, int col) {
    REQUIRE(0 <= row && row < height, "Row is out of bounds!");
    REQUIRE(0 <= col && col < width, "Column is out of bounds!");
    changeCell(row, col, new Road(row, col, this));
    main_street = {row, col};
    branches.emplace_back(std::make_pair(row, col));
    seen_cells.emplace_back(std::make_pair(row, col));
}

float CellulaireAutomaat::getScore() const {
    std::map<EStates, int> count_ = count_all();

    float score = scoreHelper(count_[EIndustrialZone], 0.1) + scoreHelper(count_[EStoreZone], 0.1) + scoreHelper(count_[EResidentialZone], 0.4)
    + scoreHelper(count_[ERoad], 0.3) - count_[EVegetation] * 0.1;
//    for (int col = 0; col < width; col++) {
//        for (int row = 0; row < height; row++) {
//            if ((*this)(row, col)->getState() == ERoad) {
//                int count;
//                for (const auto& cell: getNeighbourhood(row, col)){
//                    if (cell != nullptr && cell->getState() == ERoad) ++count;
//                }
//                if (count > 3) score -= 0.1;
//            }
//        }
//    }
    return score;
}
float CellulaireAutomaat::scoreHelper(int count, float percentage) const{
    static float total = width * height;
    float x = (count / total) / percentage;
    if (x > 1.25) return 0;
    return x;
}

void CellulaireAutomaat::updateRulesHelper(int row, int col) {
    std::vector<std::vector<EStates>> old;
    old.resize(3);
    for (int drow = 0; drow <= 2; ++drow) {
        old[drow].resize(3);
        for (int dcol = 0; dcol <= 2; ++dcol) {
            if (row + drow - 1 < 0 || row + drow - 1 >= height || col + dcol - 1 < 0 || col + dcol - 1 >= width)
                old[drow][dcol] = EVegetation;
            else
                old[drow][dcol] = (*this)(row + drow - 1, col + dcol - 1)->getState();
        }
    }
    for (int dcol = -1; dcol <= 1; ++dcol) {
        for (int drow = -1; drow <= 1; ++drow) {
            if (row + drow < 0 || row + drow >= height || col + dcol < 0 || col + dcol >= width) continue;
            if (std::find(seen_cells.begin(), seen_cells.end(), std::make_pair(row + drow, col + dcol)) != seen_cells.end()) continue;
            seen_cells.emplace_back(std::make_pair(row + drow, col + dcol));

            EStates state = static_cast<EStates>(rules[getNeighbourhoodValue(drow + 1, dcol + 1, old)]);
            if (state == old[drow + 1][dcol + 1]) {
                continue;
            }
            switch (state) {
                case EVegetation:
                    changeCell(row + drow, col + dcol, new Vegetation(*(*this)(row + drow, col + dcol)));
                    break;
                case ERoad:
                    changeCell(row + drow, col + dcol, new Road(*(*this)(row + drow, col + dcol)));
                    branches.emplace_back(std::make_pair(row + drow + drow, col + dcol + dcol));
                    break;
                case EResidentialZone:
                    changeCell(row + drow, col + dcol, new ResidentialZone(*(*this)(row + drow, col + dcol)));
                    break;
                case EIndustrialZone:
                    changeCell(row + drow, col + dcol, new IndustrialZone(*(*this)(row + drow, col + dcol)));
                    break;
                case EStoreZone:
                    changeCell(row + drow, col + dcol, new StoreZone(*(*this)(row + drow, col + dcol)));
                    break;
                default:
                    break;
            }
        }
    }
}

void CellulaireAutomaat::removeUnconnectedRoads() {
    for (int col = 0; col < width; col++) {
        for (int row = 0; row < height; row++) {
            if (!(*this)(row, col)->isConnectedTo(main_street.first, main_street.second)) {
                changeCell(row, col, new Vegetation(*(*this)(row, col)));
            }
        }
    }
}
