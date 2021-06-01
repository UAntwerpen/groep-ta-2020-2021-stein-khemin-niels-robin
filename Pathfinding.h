//
// Created by Khemin on 9-5-2021.
//

#ifndef TA_PATHFINDING_H
#define TA_PATHFINDING_H

#include "PFCell.h"
#include "CellulaireAutomaat.h"
#include <list>

class PFMask {
public:
    /**
     * Default constructor
     */
    PFMask(int width, int height);

    /**
     * Initialiseert het PFMask.
     *
     * @param cellAutomaat : PFMask wordt geinitialiseerd adv de gegevens van deze CellulaireAutomaat.
     * @param vehicle : Vehicle waarvoor PFMask wordt geinitialiseerd.
     *
     * REQUIRE(transport->getLocation() != nullptr, "transport must exist in a loaction.")
     * REQUIRE(transport->getGoal() != nullptr, "transport must have a goal.")
     */
    PFMask(CellulaireAutomaat& cellAutomaat, std::pair<int, int> goal, bool isCar = false);

    ~PFMask();

    /**
     * Geeft de width van de PFMask terug.
     *
     * @return integer
     */
    int getWidth() const;

    /**
     * Geeft de height van de PFMask terug.
     *
     * @return integer
     */
    int getHeight() const;

    /**
     * geeft de cell op rij kolom terug
     * @param row rij van de cell
     * @param column kolom can de cell
     * @return reference van de cell
     *
     * REQUIRE(0 <= row && row < width, "Row is out of bounds!")
     * REQUIRE(0 <= col && col < height, "Column is out of bounds!")
     */
    PFCell* getCell(int row, int col);

    /**
     * Geeft de integer waarden van de buur Cellen terug.
     *
     * @param row : rij index van de PFCell waarvoor de integer values van de buren worden opgevraagd
     * @param col : kolom index van de PFCell waarvoor de integer values van de buren worden opgevraagd
     *
     * @return vector van integers
     */
    std::vector<int> getNeighbourInts(int row, int col);

    /**
     * Geeft de buren van de PFCell terug.
     *
     * @param row : rij index van de PFCell waarvoor de integer values van de buren worden opgevraagd
     * @param col : kolom index van de PFCell waarvoor de integer values van de buren worden opgevraagd
     *
     * @return vector van PFCell class pointers
     */
    std::vector<PFCell*> getNeighbours(int row, int col);

    /**
     * Updates het PFMask door iedere PFCell 1 transitie te laten maken volgens volgende regels.
     * regels:
     *      Muur (niet begaanbare PFCell) ==> Muur
     *      Goal (target PFcell) ==> Goal
     *      Begaanbare PFCell : value ==> min(PFCell.getNeigbourIntegerValues()) + 1
     *
     * @return boolean : true indien er een verandering gemaakt is, anders false.
     */
     bool update();

     /**
      * Het PFMask update zichzelf totdat er geen veranderingen meer optreden.
      */
     void generateMask();


private:
    int width;
    int height;

    std::vector<std::vector<PFCell*>> mask;
};


#endif //TA_PATHFINDING_H
