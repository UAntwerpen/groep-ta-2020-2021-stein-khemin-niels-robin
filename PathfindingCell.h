//
// Created by Khemin on 9-5-2021.
//

#ifndef TA_PATHFINDINGCELL_H
#define TA_PATHFINDINGCELL_H

#include "lib/DesignByContract.h"

class PFCell {
private:
    bool passable;
    bool goal;

    int value;

public:
    /**
     * Initialiseert de PFCell
     *
     * @param passable : boolean : true als de cell begaanbaar is, anders false
     * @param goal : boolean : true als de cell een goal is, anders false
     * @param value : integer : de integer waarde van de cell
     */
    PFCell(bool passable, bool goal, int value = 0);

    /**
     * Geeft terug of de PFCell begaanbaar is, of niet
     *
     * @return boolean: true als de cell begaanbaar is, anders false
     */
    bool getPassable() const;

    /**
     * Zet passable attribuut gelijk aan de gegeven waarde p
     *
     * @param p : boolean
     *
     * ENSURE(this->getPassable() == p, "setPassable post condition failure")
     */
    void setPassable(bool p);

    /**
     * Geeft terug of de PFCell een Goal is, of niet
     *
     * @return boolean: true de cell een doel is, anders false
     */
    bool getGoal() const;

    /**
     * Zet goal attribuut gelijk aan de gegeven waarde g
     *
     * @param g : boolean
     *
     * ENSURE(this->getGoal() == g, "setGoal post condition failure")
     */
    void setGoal(bool g);

    /**
     * Geeft de integer waarde van de PFCell terug
     *
     * @return integer
     *
     * REQUIRE(this->getPassable() == true, "Only passable PFCells have integer values.")
     */
    int getValue() const;

    /**
     * Zet de integer waarde gelijk aan de gegeven waarde v
     *
     * @param v : integer
     *
     * ENSURE(this->getValue() == v, "setValue post condition failure")
     */
    void setValue(int v);
};


#endif //TA_PATHFINDINGCELL_H