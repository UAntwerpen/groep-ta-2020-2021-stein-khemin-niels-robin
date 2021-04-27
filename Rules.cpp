#include <ctime>

#include "Rules.h"
#include "Utils.h"

namespace GeneticAlgorithm {
    std::random_device rd;
    std::mt19937 mt(rd());
    void initialize_variations(){
        for (int b10 = 0; b10 <= GENOME_SIZE; b10++){
            variations[b10] = toBase5(b10);
        };
    }

    Genome* generateGenome(){
        Genome* output = new Genome;
        std::uniform_int_distribution<int> dist(0, 4);
#pragma omp parallel for if (PARALLELISM_ENABLED)
        for (int i = 0; i < GENOME_SIZE; i++){
            output->at(i) = static_cast<EStates>(dist(mt));
        }
        return output;
    }

    Population generatePopulation(){
        Population newpopu;
#pragma omp parallel for if (PARALLELISM_ENABLED)
        for (int i = 0; i < POPULATION_SIZE; i++){
            newpopu[i] = generateGenome();
        }
        return newpopu;
    }

    float fitness(Genome& G){
        // do simulation
        int correct = 0;
        for (int i = 0; i < GENOME_SIZE; i++){
            if (intToEState(i % 5) == G[i]){
                correct++;
            }
        }
        return (float)correct / GENOME_SIZE;
    }

    std::pair<Genome*, Genome*> crossover(const Genome& G1, const Genome& G2){
        Genome* G1_cross = new Genome(G1);
        Genome* G2_cross = new Genome(G2);
        std::uniform_int_distribution<int> dist_pos(0, GENOME_SIZE);
        for (int _ = 0; _ < 2; _++) {
            int crossover_point = dist_pos(mt);
            if (crossover_point < GENOME_SIZE / 2) {
#pragma omp parallel for if (PARALLELISM_ENABLED)
                for (int i = 0; i < crossover_point; i++) {
                    EStates temp = (*G1_cross)[i];
                    (*G1_cross)[i] = (*G2_cross)[i];
                    (*G2_cross)[i] = temp;
                }
            } else {
#pragma omp parallel for if (PARALLELISM_ENABLED)
                for (int i = crossover_point; i < GENOME_SIZE; i++) {
                    EStates temp = (*G1_cross)[i];
                    (*G1_cross)[i] = (*G2_cross)[i];
                    (*G2_cross)[i] = temp;
                }
            }
        }
        return std::make_pair(G1_cross, G2_cross);
    }

    void mutate(Genome& G){
        std::uniform_int_distribution<int> dist_pos(0, GENOME_SIZE);
        std::uniform_int_distribution<int> dist_switch(0, 4);
        std::uniform_int_distribution<int> dist_times(0, 7);

        for (int _ = 0, end = dist_times(mt); _ < end; _++){
            G[dist_pos(mt)] = static_cast<EStates>(dist_switch(mt));
        }
    }

    std::pair<Genome*, Genome*> parent_selection(Population& P, Weights& weights){
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
