//
// Created by Khemin on 9-5-2021.
//

#ifndef TA_PFCELL_H
#define TA_PFCELL_H

#include "lib/DesignByContract.h"
#include "Cell.h"
#include <limits>

class PFCell : public Cell {
private:
    bool passable;
    bool goal;
    int value;

public:
    /**
     * Default Constructor
     */
    PFCell();

    /**
     * Initialiseert de PFCell
     *
     * @param passable : boolean : true als de cell begaanbaar is, anders false
     * @param goal : boolean : true als de cell een goal is, anders false
     * @param value : integer : de integer waarde van de cell
     */
    PFCell(bool passable, int row, int col, bool goal = false);

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

    /**
     * Update de PFCell volgens de transitieregels.
     * regels:
     *      Muur (niet begaanbare PFCell) ==> Muur
     *      Goal (target PFcell) ==> Goal
     *      Begaanbare PFCell : value ==> min(PFCell.getNeigbourIntegerValues()) + 1
     *
     * @return bool : true als updateRules een verandering maakt aan de PFCell, anders false
     */
    bool updatePFCell(int min);

    /*!
     * Geeft de gepaste enum waarde terug
     *
     * @return enum waarde
     */
    EStates getState() const override;

    void update() override;
};


#endif //TA_PFCELL_H
