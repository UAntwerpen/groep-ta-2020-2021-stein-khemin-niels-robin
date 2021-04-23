//
// Created by nibor on 22/04/2021.
//

#ifndef TA_RULES_H
#define TA_RULES_H

#include <array>
#include <cmath>
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>
#include "Lib.h"


class Rules {

};

namespace GeneticAlgorithm {
    // https://www.youtube.com/watch?v=nhT56blfRpE&t=76s&ab_channel=KieCodes
    static std::array<std::string, GENOME_SIZE> variations;

    using Genome = std::array<EStates, GENOME_SIZE>;
    using Population = std::array<Genome, POPULATION_SIZE>;

    void initialize_variations();
    Genome generateGenome();
    Population generatePopulation();
    float fitness(Genome& G);
    void crossover(Genome& G1, Genome& G2);
    void pair_selection(Population& P);
}


#endif //TA_RULES_H
