#ifndef TA_GENETICALGORITHM_H
#define TA_GENETICALGORITHM_H

#include <array>
#include <cmath>
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>

#include "Lib.h"
#include "lib/DesignByContract.h"

// https://www.youtube.com/watch?v=nhT56blfRpE&t=76s&ab_channel=KieCodes

class Genome: public std::vector<EStates> {
public:

    void mutate(std::mt19937& mt){
        std::uniform_int_distribution<int> dist_pos(0, size() - 1);
        std::uniform_int_distribution<int> dist_switch(0, 4);
        std::poisson_distribution<int> dist_times(size() * 0.00001);

        for (int _ = 0, end = dist_times(mt); _ < end; _++){
            (*this)[dist_pos(mt)] = static_cast<EStates>(dist_switch(mt));
        }
    }

    std::pair<Genome*, Genome*> crossover(const Genome& G2, std::mt19937& mt){
        Genome* G1_cross = new Genome(*this);
        Genome* G2_cross = new Genome(G2);
        std::uniform_int_distribution<int> dist_pos(0, size());
        for (int _ = 0; _ < 2; _++) {
            int crossover_point = dist_pos(mt);
            if (crossover_point < size() / 2) {
                #pragma omp parallel for simd if (PARALLELISM_ENABLED)
                for (int i = 0; i < crossover_point; i++) {
                    EStates temp = (*G1_cross)[i];
                    (*G1_cross)[i] = (*G2_cross)[i];
                    (*G2_cross)[i] = temp;
                }
            } else {
                #pragma omp parallel for simd if (PARALLELISM_ENABLED)
                for (int i = crossover_point; i < size(); i++) {
                    EStates temp = (*G1_cross)[i];
                    (*G1_cross)[i] = (*G2_cross)[i];
                    (*G2_cross)[i] = temp;
                }
            }
        }
        return std::make_pair(G1_cross, G2_cross);
    }

    static std::pair<Genome*, Genome*> crossover(const Genome& G1, const Genome& G2, std::mt19937& mt){
        ENSURE(G1.size() == G2.size(), "Genomes are not of the same size!");
        Genome* G1_cross = new Genome(G1);
        Genome* G2_cross = new Genome(G2);
        std::uniform_int_distribution<int> dist_pos(0, G1.size());
        for (int _ = 0; _ < 2; _++) {
            int crossover_point = dist_pos(mt);
            if (crossover_point < G1.size() / 2) {
                #pragma omp parallel for simd if (PARALLELISM_ENABLED)
                for (int i = 0; i < crossover_point; i++) {
                    EStates temp = (*G1_cross)[i];
                    (*G1_cross)[i] = (*G2_cross)[i];
                    (*G2_cross)[i] = temp;
                }
            } else {
                #pragma omp parallel for simd if (PARALLELISM_ENABLED)
                for (int i = crossover_point; i < G1.size(); i++) {
                    EStates temp = (*G1_cross)[i];
                    (*G1_cross)[i] = (*G2_cross)[i];
                    (*G2_cross)[i] = temp;
                }
            }
        }
        return std::make_pair(G1_cross, G2_cross);
    }

    std::string to_string(){
        std::string s;
        for (char c: *this){
            s += c;
        }
        return s;
    }
};


using Population = std::vector<Genome*>;
using Weights = std::vector<double>;

class GeneticAlgorith{
public:

    GeneticAlgorith(int genomeSize, int populationSize);

    virtual ~GeneticAlgorith();

    Genome* generateGenome();

    void generatePopulation();

    Genome run(int max_gen);

    float calc_fitness(Genome& G);

private:
    Population population;
    Weights fitness;
    std::vector<int> indices;
    int population_size;
    int genome_size;
    std::random_device rd;
    std::mt19937* mt;
};


#endif //TA_GENETICALGORITHM_H
