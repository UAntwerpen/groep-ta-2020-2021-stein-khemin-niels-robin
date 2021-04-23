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
    std::pair<Genome&, Genome&> pair_selection(Population& P){
        float total_weight = 0;
        std::array<float, POPULATION_SIZE> fitnesses;
        std::array<int, POPULATION_SIZE> genomes;
        std::random_device rd;
        std::mt19937 mt(rd());
        std::poisson_distribution<int> dist(1);

        for (int i = 0; i < P.size(); i++){
            fitnesses[i] = fitness(P[i]);
            genomes[i] = i;
        }
        std::array<std::pair<int, int> , POPULATION_SIZE / 2> parents;
        std::sort(genomes.begin(), genomes.end(), [&fitnesses](int g1, int g2){return fitnesses[g1] > fitnesses[g2];});
        int first = dist(rd);
        int second = dist(rd);
        while (first == second) second = dist(rd);
        return std::make_pair(P[genomes[first], P[genomes[second]]]);
    }
}
