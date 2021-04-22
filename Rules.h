//
// Created by nibor on 22/04/2021.
//

#ifndef TA_RULES_H
#define TA_RULES_H

#include <array>
#include <cmath>
#include <algorithm>
#include <random>
#include "Lib.h"


class Rules {

};

namespace GeneticAlgorithm {

    static std::array<std::string, 390625> variations;


    using Genome = std::array<EStates, 390625>;

    Genome generateGenome();
}


#endif //TA_RULES_H
