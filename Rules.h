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
    using Population = std::array<Genome*, POPULATION_SIZE>;
    using Weights = std::array<float, POPULATION_SIZE>;

    void initialize_variations();
    Genome generateGenome();
    Population generatePopulation();
    float fitness(Genome& G);
    std::pair<Genome, Genome> crossover(Genome& G1, Genome& G2);
    void mutate(Genome& G);
    std::pair<Genome*, Genome*> parent_selection(Population& P, Weights& weights);
}


#endif //TA_RULES_H
