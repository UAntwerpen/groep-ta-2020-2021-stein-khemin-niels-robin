#include <iomanip>
#include <QApplication>
#include <array>

#include "MainWindow.h"
#include "CellulaireAutomaat.h"
#include "GeneticAlgorithm.h"
#include "Pathfinding.h"
#include "CitySimulation.h"

using namespace std;
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    GeneticAlgorith algo(390624, 250);

    Genome rule = algo.run(1000);
//    string s;
//    std::ifstream file("latest001.txt", std::ifstream::binary);
//    while (file.good()){
//        s += file.get();
//    }

    CitySimulation city;
    city.runSimulationGUI(20, 20, rule.to_string());
    return 0;
}
