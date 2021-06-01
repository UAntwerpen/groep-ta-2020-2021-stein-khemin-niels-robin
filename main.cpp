#include <iomanip>
#include <array>

#include "CellulaireAutomaat.h"
#include "GeneticAlgorithm.h"
#include "Pathfinding.h"
#include "CitySimulation.h"

using namespace std;
int main(int argc, char *argv[]){
//    GeneticAlgorith algo(390624, 500);
//
//    Genome rule = algo.run(200);
    string s;
    std::ifstream file("../Maps/rule008.txt", std::ifstream::binary);
    while (file.good()){
        s += file.get();
    }
    std::cout << "run" << std::endl;
    CitySimulation city;
    city.runSimulationGUI(20, 20, s);
    return 0;
}
