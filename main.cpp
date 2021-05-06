#include <iostream>
#include <algorithm>
#include <iomanip>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>


#include "CellulaireAutomaat.h"
#include "Rules.h"


int main(int argc, char *argv[]){
//    QApplication a(argc, argv);
//    QGraphicsScene * scene = new QGraphicsScene();
//    QGraphicsRectItem * rect = new QGraphicsRectItem();
//    rect->setRect(0,0,100,100);
//    scene->addItem(rect);
//    QGraphicsView * view = new QGraphicsView(scene);
//    view->show();


//    std::string rule;
//    for (const auto& c: *GeneticAlgorithm::generateGenome()){
//        rule += std::to_string(c);
//    }
//    CellulaireAutomaat C(2, 2, rule);
//    GeneticAlgorithm::Population population = GeneticAlgorithm::generatePopulation();
//    GeneticAlgorithm::Weights fitness;
//    std::array<int, POPULATION_SIZE> indices{};
//    for (int i = 0; i < POPULATION_SIZE;i++) indices[i] = i;
//
//    // main loop
//    for (int _ = 0; _ < GENERATION_LIMIT && fitness[indices[0]] != 1; _++){
//        std::cout << "Running Generation: " << _ << std::endl;
//#pragma omp parallel for
//        for (int i = 0; i < POPULATION_SIZE; i++){
//            fitness[i] = GeneticAlgorithm::fitness(*population[i]);
//        }
//        std::sort(indices.begin(), indices.end(), [&fitness](int first, int second){return fitness[first] > fitness[second];});
//
//        GeneticAlgorithm::Population next_gen;
//
//        // keep 2 best rules
//        next_gen[0] = population[indices[0]];
//        next_gen[1] = population[indices[1]];
////        next_gen[2] = population[indices[2]];
////        next_gen[3] = population[indices[3]];
//
//        std::cout << fitness[indices[0]] << std::endl;
//        int index = 2;
//        while (index < POPULATION_SIZE){
////            std::pair<GeneticAlgorithm::Genome*, GeneticAlgorithm::Genome*> parents = GeneticAlgorithm::parent_selection(population, fitness);
//            std::pair<GeneticAlgorithm::Genome*, GeneticAlgorithm::Genome*> children = GeneticAlgorithm::crossover(*next_gen[0], *next_gen[1]);
//            GeneticAlgorithm::mutate(*children.first);
//            GeneticAlgorithm::mutate(*children.second);
//            next_gen[index] = children.first;
//            index++;
//            if (index < POPULATION_SIZE) {
//                next_gen[index] = children.second;
//            }
//            index++;
//        }
//        for (int i = 2; i < POPULATION_SIZE;i++){
//            delete population[indices[i]];
//        }
//        population = next_gen;
//    }
//    for (const auto& s: *(population[0])){
//        std::cout << s;
//    }
    return 0/*a.exec()*/;
}
