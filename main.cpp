#include <iostream>
#include <algorithm>

#include "CellulaireAutomaat.h"
#include "Rules.h"


int main(){
//    CellulaireAutomaat C(2, 2);
    GeneticAlgorithm::Population population = GeneticAlgorithm::generatePopulation();
    GeneticAlgorithm::Weights fitness;
    std::array<int, POPULATION_SIZE> indices{};
    for (int i = 0; i < POPULATION_SIZE;i++) indices[i] = i;

    // main loop
    for (int _ = 0; _ < GENERATION_LIMIT; _++){
        for (int i = 0; i < POPULATION_SIZE; i++){
            fitness[i] = GeneticAlgorithm::fitness(*population[i]);
        }
        std::sort(indices.begin(), indices.end(), [&fitness](int first, int second){return fitness[first] > fitness[second];});

        GeneticAlgorithm::Population next_gen;

        // keep 2 best rules
        next_gen[0] = population[indices[0]];
        next_gen[1] = population[indices[1]];

        for (int i = 0; i < (POPULATION_SIZE / 2) - 2; i++){
            int index = (i * 2) + 2;
            std::pair<GeneticAlgorithm::Genome*, GeneticAlgorithm::Genome*> parents = GeneticAlgorithm::parent_selection(population, fitness);
            std::pair<GeneticAlgorithm::Genome, GeneticAlgorithm::Genome> children = GeneticAlgorithm::crossover(*parents.first, *parents.second);
            GeneticAlgorithm::mutate(children.first);
            GeneticAlgorithm::mutate(children.second);
            next_gen[index] = &children.first;
            next_gen[index + 1] = &children.first;
        }
        population = next_gen;
    }

    return 0;
}
