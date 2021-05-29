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
    GeneticAlgorith algo(390624, 50);

    Genome rule = algo.run(50);
    string s;
    for(char c: rule){
        s += c;
    }
//    string s;
//    std::ifstream file("latest001.txt", std::ifstream::binary);
//    while (file.good()){
//        s += file.get();
//   }

    CitySimulation city;
    city.runSimulationGUI(20, 20, s);
    return 0;
}
