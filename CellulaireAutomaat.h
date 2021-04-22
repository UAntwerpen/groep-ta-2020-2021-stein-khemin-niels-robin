#ifndef TA_CELLULAIREAUTOMAAT_H
#define TA_CELLULAIREAUTOMAAT_H

#include <vector>
#include "Cell.h"

class CellulaireAutomaat {
public:
    CellulaireAutomaat(int width, int height);

    Cell& operator()(int row, int column);

    std::vector<Cell*> getNeighbourhood(int row, int col);

private:
    int width;
    int height;
    Cell* matrix;
};

#endif //TA_CELLULAIREAUTOMAAT_H
