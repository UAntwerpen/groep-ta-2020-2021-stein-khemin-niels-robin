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

    Genome<GENOME_SIZE> rule = algo.run(10);
    string s;
    for(char c: rule){
        s += c;
    }
    CellulaireAutomaat A(10,10, s);
    A.addMainStreet(0, 5);
    A.draw();
    std::cout << '\a';
    return QApplication::exec();
}
