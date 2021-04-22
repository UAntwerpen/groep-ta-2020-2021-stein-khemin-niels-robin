

#ifndef TA_CELL_H
#define TA_CELL_H

#include "Lib.h"

class Cell {
public:
    Cell();

    virtual EStates getState();

private:
    int row;
    int col;
    double happiness;
};


#endif //TA_CELL_H
