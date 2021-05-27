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



// https://www.youtube.com/watch?v=nhT56blfRpE&t=76s&ab_channel=KieCodes

template< std::size_t _Nm>
class Genome: public std::array<EStates, _Nm> {
public:
    Genome() = default;

    Genome(EStates states) {

    }

    void mutate(std::mt19937& mt){
        std::uniform_int_distribution<int> dist_pos(0, GENOME_SIZE - 1);
        std::uniform_int_distribution<int> dist_switch(0, 4);
        std::uniform_int_distribution<int> dist_times(0, GENOME_SIZE * 0.00001);

        for (int _ = 0, end = dist_times(mt); _ < end; _++){
            (*this)[dist_pos(mt)] = static_cast<EStates>(dist_switch(mt));
        }
    }

    std::pair<Genome<_Nm>, Genome<_Nm>> crossover(const Genome<_Nm>& G2, std::mt19937& mt){
        Genome* G1_cross = new Genome(this);
        Genome* G2_cross = new Genome(G2);
        std::uniform_int_distribution<int> dist_pos(0, GENOME_SIZE);
        for (int _ = 0; _ < 2; _++) {
            int crossover_point = dist_pos(mt);
            if (crossover_point < GENOME_SIZE / 2) {
                #pragma omp parallel for simd if (PARALLELISM_ENABLED)
                for (int i = 0; i < crossover_point; i++) {
                    EStates temp = (*G1_cross)[i];
                    (*G1_cross)[i] = (*G2_cross)[i];
                    (*G2_cross)[i] = temp;
                }
            } else {
                #pragma omp parallel for simd if (PARALLELISM_ENABLED)
                for (int i = crossover_point; i < GENOME_SIZE; i++) {
                    EStates temp = (*G1_cross)[i];
                    (*G1_cross)[i] = (*G2_cross)[i];
                    (*G2_cross)[i] = temp;
                }
            }
        }
        return std::make_pair(G1_cross, G2_cross);
    }

    static std::pair<Genome<_Nm>*, Genome<_Nm>*> crossover(const Genome<_Nm>& G1, const Genome<_Nm>& G2, std::mt19937& mt){
        Genome* G1_cross = new Genome(G1);
        Genome* G2_cross = new Genome(G2);
        std::uniform_int_distribution<int> dist_pos(0, GENOME_SIZE);
        for (int _ = 0; _ < 2; _++) {
            int crossover_point = dist_pos(mt);
            if (crossover_point < GENOME_SIZE / 2) {
                #pragma omp parallel for simd if (PARALLELISM_ENABLED)
                for (int i = 0; i < crossover_point; i++) {
                    EStates temp = (*G1_cross)[i];
                    (*G1_cross)[i] = (*G2_cross)[i];
                    (*G2_cross)[i] = temp;
                }
            } else {
                #pragma omp parallel for simd if (PARALLELISM_ENABLED)
                for (int i = crossover_point; i < GENOME_SIZE; i++) {
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
        for (char c: this){
            s += c;
        }
        return s;
    }
};


using Population = std::array<Genome<GENOME_SIZE>*, POPULATION_SIZE>;
using Weights = std::array<double, POPULATION_SIZE>;

class GeneticAlgorith{
public:

    GeneticAlgorith();

    Genome<GENOME_SIZE>* generateGenome();

    void generatePopulation();

    Genome<GENOME_SIZE> run(int max_gen);

    float calc_fitness(Genome<GENOME_SIZE>& G);

private:
    Population population;
    Weights fitness;
    std::array<int, POPULATION_SIZE> indices;
    int population_size;
    int genome_size;
    std::random_device rd;
    std::mt19937* mt;
};


#endif //TA_RULES_H
