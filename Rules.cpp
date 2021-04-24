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
#pragma omp parallel for if (PARALLELISM_ENABLED)
        for (int i = 0; i < GENOME_SIZE; i++){
            output[i] = static_cast<EStates>(input[dist(mt)]);
        }
        return output;
    }

    Population generatePopulation(){
        Population newpopu;
#pragma omp parallel for if (PARALLELISM_ENABLED)
        for (int i = 0; i < POPULATION_SIZE; i++){
            newpopu[i] = generateGenome();
        }
    }

    float fitness(Genome& G){
        // do simulation
        return 0.f;
    }

    std::pair<Genome, Genome> crossover(Genome G1, Genome G2){
        int crossover_point = rand() % GENOME_SIZE;
        if(crossover_point < GENOME_SIZE / 2) {
#pragma omp parallel for if (PARALLELISM_ENABLED)
            for (int i = 0; i < crossover_point; i++) {
                std::swap(G1[i], G2[i]);
            }
        } else {
#pragma omp parallel for if (PARALLELISM_ENABLED)
            for (int i = crossover_point; i < GENOME_SIZE; i++) {
                std::swap(G1[i], G2[i]);
            }
        }
        return std::make_pair(G1, G2);
    }

    void mutate(Genome& G){
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist_pos(0, GENOME_SIZE);
        std::uniform_int_distribution<int> dist_switch(0, 5);
        std::uniform_int_distribution<int> dist_times(0, 100);

        for (int _ = 0, end = dist_times(mt); _ < end; _++){
            G[dist_pos(mt)] = static_cast<EStates>(dist_switch(mt));
        }
    }

    std::pair<Genome*, Genome*> parent_selection(Population& P, Weights& weights){
        std::random_device rd;
        std::mt19937 mt(rd());

        std::array<int, POPULATION_SIZE> indices{};
        for (int i = 0; i < POPULATION_SIZE;i++) indices[i] = i;

        std::piecewise_constant_distribution<double> dist(indices.begin(),indices.end(),weights.begin());
        //        std::geometric_distribution<int> dist(0.3);

        std::sort(indices.begin(), indices.end(), [&weights](int first, int second){return weights[first] > weights[second];});
        int first = static_cast<int>(std::round(dist(mt)));
        int second = static_cast<int>(std::round(dist(mt)));
        while (first == second) second = static_cast<int>(std::round(dist(mt)));

        return std::make_pair(P[indices[first]], P[indices[second]]);
    }
}
