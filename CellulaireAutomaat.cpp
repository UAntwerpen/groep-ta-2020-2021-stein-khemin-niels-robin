
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
    //w = nullptr;
    w = new MainWindow(width, height, this);
    //draw();
    w->show();
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
    REQUIRE(0 <= row && row < width, "Row with is out of bounds!");
    REQUIRE(0 <= column && column < height, "Column is out of bounds!");
    return matrix[row * height + column];
}

std::vector<Cell *> CellulaireAutomaat::getNeighbourhood(int row, int col) {
    REQUIRE(0 <= row && row < height, "Row is out of bounds!");
    REQUIRE(0 <= col && col < width, "Column is out of bounds!");
    std::vector<Cell *> neighbourhood(8);

    neighbourhood[0] = 0 <= row && 0 <= col ? (*this)(row - 1, col - 1) : nullptr;
    neighbourhood[1] = 0 <= row ? (*this)(row - 1, col) : nullptr;
    neighbourhood[2] = 0 <= row && col < width ? (*this)(row - 1, col + 1) : nullptr;
    neighbourhood[3] = col < width ? (*this)(row, col + 1) : nullptr;
    neighbourhood[4] = row < height && col < width ? (*this)(row + 1, col + 1) : nullptr;
    neighbourhood[5] = row < height ? (*this)(row + 1, col) : nullptr;
    neighbourhood[6] = row < height && 0 <= col ? (*this)(row + 1, col - 1) : nullptr;
    neighbourhood[7] = 0 <= col ? (*this)(row, col - 1) : nullptr;
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

void CellulaireAutomaat::changeCell(int row, int column, Cell *to) {
    REQUIRE(0 <= row && row < height, "Row is out of bounds!");
    REQUIRE(0 <= column && column < width, "Column is out of bounds!");
    REQUIRE(to != nullptr, "De gegeven cell is een nullptr!");
    delete matrix[row * height + column];
    //matrix[row * height + column] = to;
    matrix[(row) * height + (column)] = to;
}

void CellulaireAutomaat::updateRules() {
    CellFactorySingleton& factory = CellFactorySingleton::getInstance();
    for (int col = 0; col < width; col++) {
        for (int row = 0; row < height; row++) {
            EStates state = static_cast<EStates>(rules[getNeighbourhoodValue(row, col)]);
            if (state == (*this)(row, col)->getState()) {
                continue;
            }
            Cell *new_cell = factory.getCell(state);
            changeCell(row, col, new_cell);
        }
    }
    w->updateAll();
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

    void CellulaireAutomaat::draw() {
        w->updateAll();
        /*for (int col = 0; col < width; col++){
            for (int row = 0; row < height; row++){
                switch ((*this)(row, col)->getState()) {
                    case 1:
                        std::cout << "r ";
                    case 2:
                        std::cout << "R ";
                        break;
                    case 3:
                        std::cout << "I ";
                        break;
                    case 4:
                        std::cout << "S ";
                    case 0:
                    default:
                        std::cout << "V ";
                        break;
                }
            }
            std::cout << std::endl;
        }*/
    }
