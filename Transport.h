//
// Created by Khemin on 1-5-2021.
//

#ifndef TA_TRANSPORT_H
#define TA_TRANSPORT_H

class Cell;


class Transport {
public:
    /**
     * Returns a pointer to the cell where the vehicle is currently located.
     *
     * @return Pointer to the Cell containing the Vehicle.
     */
    Cell* getLocation();

    /**
     * Sets the location attribute of the Vehicle to the given value.
     *
     * @param cell : new location of the Vehicle
     *
     * ENSURE(this->getLocation() == cell, "location not set to given value (post condition failure)")
     */
    void setLocation(Cell* cell);

private:
    // not owner of cell, Don't delete!
    Cell* location;

};


#endif //TA_TRANSPORT_H
