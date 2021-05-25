#include <iostream>
#include <algorithm>
#include <iomanip>
#include <QApplication>
#include <array>

#include "MainWindow.h"
#include "CellulaireAutomaat.h"
#include "Rules.h"
#include "Pathfinding.h"
#include "settingswindow.h"
#include "CitySimulation.h"

using namespace std;
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    GeneticAlgorith algo(GENOME_SIZE, 10);
    //algo.run(10);
    Genome<GENOME_SIZE> *rule = algo.generateGenome();
    string s;
    for(char c: *rule){
        s += c;
    }
    CitySimulation city;
    city.runSimulation(s);
    return QApplication::exec();
}
