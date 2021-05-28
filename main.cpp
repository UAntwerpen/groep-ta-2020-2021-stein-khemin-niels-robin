#include <iostream>
#include <algorithm>
#include <iomanip>
#include <QApplication>
#include <QTime>
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
    GeneticAlgorith algo;

    Genome<GENOME_SIZE> rule = algo.run(5);
    string s;
    for(char c: rule){
        s += c;
    }
    CitySimulation city;
    city.runSimulationGUI(s);
    return QApplication::exec();
}
