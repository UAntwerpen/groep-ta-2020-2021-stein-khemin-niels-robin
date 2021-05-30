#include <ctime>
#include "GeneticAlgorithm.h"
#include "CitySimulation.h"



GeneticAlgorith::GeneticAlgorith(int genomeSize, int populationSize): genome_size(genomeSize), population_size(populationSize) {
    unsigned int seed = std::time(nullptr);
    std::cout << seed << std::endl;
    std::srand(seed);
    mt = new std::mt19937(std::rand());
    population.resize(population_size);
    indices.resize(population_size);
    fitness.resize(population_size);
    generatePopulation();
    for (int i = 0; i < population_size;i++) indices[i] = i;
}

void GeneticAlgorith::generatePopulation() {
#pragma omp parallel for simd if (PARALLELISM_ENABLED)
    for (int i = 0; i < population_size; i++){
        population[i] = generateGenome();
    }
}

Genome *GeneticAlgorith::generateGenome() {
    Genome* output = new Genome;
    output->resize(genome_size);
    std::uniform_int_distribution<int> dist(0, 4);
#pragma omp parallel for if (PARALLELISM_ENABLED)
    for (int i = 0; i < genome_size; i++){
        (*output)[i] = static_cast<EStates>(dist(*mt));
    }
    return output;
}

Genome GeneticAlgorith::run(int max_gen) {
    auto begin = std::chrono::system_clock::now();
    for (int _ = 0; _ < max_gen; _++){
        std::cout << "Running Generation: " << _ << std::endl;
        begin = std::chrono::system_clock::now();
#pragma omp parallel for if (PARALLELISM_ENABLED)
        for (int i = 0; i < population_size; i++){
            fitness[i] = calc_fitness(*population[i]);
        }
        std::sort(indices.begin(), indices.end(), [this](int first, int second){return fitness[first] > fitness[second];});

        Population next_gen(population_size);

        // keep 2 best rules
        next_gen[0] = population[indices[0]];
        next_gen[1] = population[indices[1]];

        std::cout << fitness[indices[0]] << std::endl;
#pragma omp parallel for simd if (PARALLELISM_ENABLED)
        for (int index = 2; index < population_size; ++index){
//            std::pair<Genome*, Genome*> parents = parent_selection(population, fitness);
            std::pair<Genome*, Genome*> children = Genome::crossover(*next_gen[0], *next_gen[1], *mt);
            children.first->mutate(*mt);
            children.second->mutate(*mt);

            next_gen[index] = children.first;
            ++index;
            if (index < population_size) {
                next_gen[index] = children.second;
            }
        }
        for (int i = 2; i < population_size;i++){
            delete population[indices[i]];
        }
        population = next_gen;
        std::chrono::duration<double> dur = std::chrono::system_clock::now() - begin;
        std::cout << "Took: " << dur.count() << "s" << std::endl;
    }
    return *(population[0]);
}

float GeneticAlgorith::calc_fitness(Genome &G) {
    CitySimulation city;
    return city.runSimulation(10, 10, G.to_string());
}

GeneticAlgorith::~GeneticAlgorith() {
    for (int i = 0; i < population_size;i++){
        delete population[i];
    }
}
