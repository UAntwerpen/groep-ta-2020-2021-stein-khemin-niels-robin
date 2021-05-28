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

using namespace std;
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    GeneticAlgorith algo;

    Genome<GENOME_SIZE> rule = algo.run(500);
    string s;
    for(char c: rule){
        s += c;
    }

//    string s;
//    std::ifstream file("149.txt", std::ifstream::binary);
//    while (file.good()){
//        s += file.get();
//    }

    CellulaireAutomaat A(10, 10, s);
    A.addMainStreet(0, 5);
    std::cout << '\a';
    return QApplication::exec();
}
