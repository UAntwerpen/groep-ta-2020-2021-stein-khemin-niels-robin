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

    /*!
     * switches the value on random locations to random value (between 0-4)
     * @param mt random device
     */
    void mutate(std::mt19937& mt){
        std::uniform_int_distribution<int> dist_pos(0, size() - 1);
        std::uniform_int_distribution<int> dist_switch(0, 4);
        std::poisson_distribution<int> dist_times(size() * 0.00001);

        for (int _ = 0, end = dist_times(mt); _ < end; _++){
            (*this)[dist_pos(mt)] = static_cast<EStates>(dist_switch(mt));
        }
    }

    /*!
     * crosses over this and G2, using random device mt
     * @param G2 second genome
     * @param mt random device
     * @return std::pair<Genome*, Genome*>
     */
    std::pair<Genome*, Genome*> crossover(const Genome& G2, std::mt19937& mt) const{
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

    /*!
     * crosses over G1 and G2, using random device mt
     * @param G1 first genome
     * @param G2 second genome
     * @param mt random device
     * @return std::pair<Genome*, Genome*>
     */
    static std::pair<Genome*, Genome*> crossover(const Genome& G1, const Genome& G2, std::mt19937& mt){
        return G1.crossover(G2, mt);
    }

    /*!
     * converts the array of chars to a string
     * @return string
     */
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

    /*!
     * trains a population to generate a genome
     * @param max_gen the number of generations for which the generation is ran
     * @return Genome
     */
    Genome run(int max_gen);

private:
    /*!
     * creates a random genome
     * @return Genome*
     */
    Genome* generateGenome();

    /*!
     * generates a random population
     */
    void generatePopulation();

    /*!
     * calculates the fitness of a genome
     * @param G
     * @return
     */
    float calc_fitness(Genome& G);


    Population population;
    Weights fitness;
    std::vector<int> indices;
    int population_size;
    int genome_size;
    std::mt19937* mt;
};


#endif //TA_GENETICALGORITHM_H
