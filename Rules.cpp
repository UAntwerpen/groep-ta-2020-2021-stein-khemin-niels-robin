#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
//
// Created by nibor on 22/04/2021.
//

#include "Rules.h"
#include "Utils.h"

namespace GeneticAlgorithm {

    void initialize_variations(){
        for (int b10 = 0; b10 <= GENOME_SIZE; b10++){
            variations[b10] = toBase5(b10);
        };
    }

    Genome generateGenome(){
        std::string input = "01234";
        Genome output;
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, 5);
#pragma omp parallel for
        for (int i = 0; i < GENOME_SIZE; i++){
            output[i] = static_cast<EStates>(input[dist(mt)]);
        }
        return output;
    }

    Population generatePopulation(){
        Population newpopu;
#pragma omp parallel for
        for (int i = 0; i < POPULATION_SIZE; i++){
            newpopu[i] = generateGenome();
        }
    }

    float fitness(Genome& G){
        // do simulation
        return 0.f;
    }

    void crossover(Genome& G1, Genome& G2){
        int crossover_point = rand() % GENOME_SIZE;
        if(crossover_point < GENOME_SIZE / 2) {
#pragma omp parallel for
            for (int i = 0; i < crossover_point; i++) {
                std::swap(G1[i], G2[i]);
            }
        } else {
#pragma omp parallel for
            for (int i = crossover_point; i < GENOME_SIZE; i++) {
                std::swap(G1[i], G2[i]);
            }
        }
    }
}
