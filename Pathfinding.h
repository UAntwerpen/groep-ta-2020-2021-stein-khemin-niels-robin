//
// Created by Khemin on 9-5-2021.
//

#ifndef TA_PATHFINDING_H
#define TA_PATHFINDING_H

#include "PFCell.h"
#include "CellulaireAutomaat.h"
#include "Transport.h"

class PFMask {
private:
    int width;
    int height;

    PFCell** mask;
public:
    /**
     * Initialiseert het PFMask.
     *
     * @param cellAutomaat : PFMask wordt geinitialiseerd adv de gegevens van deze CellulaireAutomaat.
     */
    PFMask(CellulaireAutomaat& cellAutomaat, Transport* transport);

    /**
     * Geeft de integer waarden van de buur Cellen terug.
     *
     * @param row : rij index van de PFCell waarvoor de integer values van de buren worden opgevraagd
     * @param col : kolom index van de PFCell waarvoor de integer values van de buren worden opgevraagd
     *
     * @return vector van integers
     */
    std::vector<int> getNeigbourInts(int row, int col);

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
};


#endif //TA_PATHFINDING_H
