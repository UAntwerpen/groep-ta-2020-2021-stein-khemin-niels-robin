
#include "lib/DesignByContract.h"
#include "CellulaireAutomaat.h"
#include "Lib.h"
#include "Cell.h"

CellulaireAutomaat::CellulaireAutomaat(int width, int height, const std::string& rules) : width(width), height(height), rules(rules) {
    REQUIRE(1 < width, "Width is too small(must be at least 2)!");
    REQUIRE(1 < height, "Height is too small(must be at least 2)!");
    matrix = std::vector<Cell*>(width * height);
    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            changeCell(row, col, new Vegetation(row, col, this));
        }
    }

    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    std::string name = ss.str();
    std::ofstream file(name + ".txt", std::ofstream ::trunc);
    if (file.is_open()) {
        file << rules;
    } else {
        std::cerr << "couldn't open file!" << std::endl;
    }
    file.close();
    w = nullptr;
//    w = new MainWindow(100, 100);
//    draw();
//    w->show();
}

CellulaireAutomaat::CellulaireAutomaat(const std::string &filename) {
    w = nullptr;
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
        std::cout << line << std::endl;
    }

    file.close();
}

CellulaireAutomaat::~CellulaireAutomaat() {
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    std::string filename = ss.str() + ".txt";

    std::remove(filename.c_str());
    delete w;
}

Cell* CellulaireAutomaat::operator()(int row, int column) const {
    REQUIRE(0 <= row && row < width, "Row is out of bounds!");
    REQUIRE(0 <= column && column < height, "Column is out of bounds!");
    return matrix[(row + 1) * height + (column + 1)];//TODO waarom +1?
}

std::vector<Cell *> CellulaireAutomaat::getNeighbourhood(int row, int col) {
    REQUIRE(0 <= row && row < width, "Row is out of bounds!");
    REQUIRE(0 <= col && col < height, "Column is out of bounds!");
    std::vector<Cell *> neighbourhood(8);
    neighbourhood[0] = (*this)(row - 1, col - 1);
    neighbourhood[1] = (*this)(row - 1, col);
    neighbourhood[2] = (*this)(row - 1, col + 1);
    neighbourhood[3] = (*this)(row, col + 1);
    neighbourhood[4] = (*this)(row + 1, col + 1);
    neighbourhood[5] = (*this)(row + 1, col);
    neighbourhood[6] = (*this)(row + 1, col - 1);
    neighbourhood[7] = (*this)(row, col - 1);
    return neighbourhood;
}

int CellulaireAutomaat::getNeighbourhoodValue(int row, int col) {
    REQUIRE(0 <= row && row < width, "Row is out of bounds!");
    REQUIRE(0 <= col && col < height, "Column is out of bounds!");
    int value = 0;
    static int powers[8] = {static_cast<int>(pow(5, 7)), static_cast<int>(pow(5, 6)), static_cast<int>(pow(5, 5)),
                            static_cast<int>(pow(5, 4)), static_cast<int>(pow(5, 3)),
                            static_cast<int>(pow(5, 2)), 5, 1};

    value += ((*this)(row - 1, col - 1))->getState() * powers[0];
    value += ((*this)(row - 1, col))->getState() * powers[1];
    value += ((*this)(row - 1, col + 1))->getState() * powers[2];
    value += ((*this)(row, col + 1))->getState() * powers[3];
    value += ((*this)(row + 1, col + 1))->getState() * powers[4];
    value += ((*this)(row + 1, col))->getState() * powers[5];
    value += ((*this)(row + 1, col - 1))->getState() * powers[6];
    value += ((*this)(row, col - 1))->getState() * powers[7];
    return value;
}

void CellulaireAutomaat::changeCell(int row, int column, Cell *to) {
    REQUIRE(0 <= row && row < width, "Row is out of bounds!");
    REQUIRE(0 <= column && column < height, "Column is out of bounds!");
    REQUIRE(to != nullptr, "De gegeven cell is een nullptr!");
    delete matrix[row * height + column];
    matrix[row * height + column] = to;
}

void CellulaireAutomaat::updateRules() {
    for (int col = 0; col < width; col++) {
        for (int row = 0; row < height; row++) {
            EStates state = static_cast<EStates>(rules[getNeighbourhoodValue(row, col)]);
            if (state == (*this)(row, col)->getState()) {
                (*this)(row, col)->update();
                if (state == (*this)(row, col)->getState()) {
                    continue;
                }
                Cell *new_cell = new Vegetation(row, col, this); //TODO
                changeCell(row, col, new_cell);
            }
        }
    }
}

void CellulaireAutomaat::updateCells() {
    for (int col = 0; col < width; col++) {
        for (int row = 0; row < height; row++) {
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

std::map<EStates, int> CellulaireAutomaat::count_all() const {
    std::map<EStates, int> counters;
    counters[static_cast<EStates>(0)] = 0;
    counters[static_cast<EStates>(1)] = 0;
    counters[static_cast<EStates>(2)] = 0;
    counters[static_cast<EStates>(3)] = 0;
    counters[static_cast<EStates>(4)] = 0;
    for (int col = 0; col < width; col++) {
        for (int row = 0; row < height; row++) {
            EStates cell_state = (*this)(row, col)->getState();
            counters[cell_state]++;
        }
    }
    return counters;
}

int CellulaireAutomaat::count(const EStates &state, int row, int col, int radius) const {
    int counter = 0;
    for (int c = col-radius; c <= col+radius; c++){
        for (int r = row-radius; r <= row+radius; r++){
            if(r >= 0 && r < width && c >= 0 && c < height && (*this)(r, c).getState() == state){
                    counter++;
            }
        }
    }
    return counter;
}

    int CellulaireAutomaat::getWidth() const {
        ENSURE(width > 0, "Width is less then 0!");
        return width;
    }

    int CellulaireAutomaat::getHeight() const {
        ENSURE(height > 0, "Height is less then 0!");
        return height;
    }

    void CellulaireAutomaat::draw() {
//    for (int col = 0; col < width; col++){
//        for (int row = 0; row < height; row++){
//            w->drawTile(row, col, 0, (*this)(row, col).getPixelArt());
//        }
//    }
    }
