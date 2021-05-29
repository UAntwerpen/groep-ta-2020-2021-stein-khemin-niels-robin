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
#include "CitySimulation.h"

using namespace std;
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    GeneticAlgorith algo;
/*
    Genome<GENOME_SIZE> rule = algo.run(100);
    string s;
    for(char c: rule){
        s += c;
    }*/
    string s;
    std::ifstream file("0xfbad80.txt", std::ifstream::binary);
    while (file.good()){
        s += file.get();
    }

    CitySimulation city;
    city.runSimulationGUI(s);
    return QApplication::exec();
}
