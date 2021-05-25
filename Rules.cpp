#include <ctime>

#include "Rules.h"
#include "Utils.h"
#include "CitySimulation.h"



GeneticAlgorith::GeneticAlgorith(int genomeSize, int populationSize) {
    population_size = populationSize;
    genome_size = genomeSize;
    std::srand(time(NULL));
    mt = new std::mt19937(rd());
    generatePopulation();
    for (int i = 0; i < POPULATION_SIZE;i++) indices[i] = i;
}

void GeneticAlgorith::generatePopulation() {
#pragma omp parallel for simd if (PARALLELISM_ENABLED)
    for (int i = 0; i < POPULATION_SIZE; i++){
        population[i] = generateGenome();
    }
}

Genome<GENOME_SIZE> *GeneticAlgorith::generateGenome() {
    Genome<GENOME_SIZE>* output = new Genome<GENOME_SIZE>;
    std::uniform_int_distribution<int> dist(0, 4);
#pragma omp parallel for if (PARALLELISM_ENABLED)
    for (int i = 0; i < GENOME_SIZE; i++){
        output->at(i) = static_cast<EStates>(dist(*mt));
    }
    return output;
}

Genome<GENOME_SIZE> GeneticAlgorith::run(int max_gen) {
    for (int _ = 0; _ < GENERATION_LIMIT && fitness[indices[0]] != 1; _++){
        std::cout << "Running Generation: " << _ << std::endl;
//#pragma omp parallel for if (PARALLELISM_ENABLED)
        for (int i = 0; i < POPULATION_SIZE; i++){
            fitness[i] = calc_fitness(*population[i]);
        }
        std::sort(indices.begin(), indices.end(), [this](int first, int second){return fitness[first] > fitness[second];});

        Population next_gen;

        // keep 2 best rules
        next_gen[0] = population[indices[0]];
        next_gen[1] = population[indices[1]];

        std::cout << fitness[indices[0]] << std::endl;
        int index = 2;
        while (index < POPULATION_SIZE){
//            std::pair<Genome*, Genome*> parents = parent_selection(population, fitness);
            std::pair<Genome<GENOME_SIZE>*, Genome<GENOME_SIZE>*> children = Genome<GENOME_SIZE>::crossover(*next_gen[0], *next_gen[1], *mt);
            children.first->mutate(*mt);
            children.second->mutate(*mt);

            next_gen[index] = children.first;
            index++;
            if (index < POPULATION_SIZE) {
                next_gen[index] = children.second;
            }
            index++;
        }
        for (int i = 2; i < POPULATION_SIZE;i++){
            delete population[indices[i]];
        }
        population = next_gen;
    }
    for (const auto& s: *(population[0])){
        std::cout << s;
    }
    return *(population[0]);
}

float GeneticAlgorith::calc_fitness(Genome<GENOME_SIZE> &G) {
    std::string rules;
    for (char c: G){
        rules += c;
    }
    return runSimulation(rules);
}
