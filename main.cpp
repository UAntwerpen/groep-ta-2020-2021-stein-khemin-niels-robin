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
    GeneticAlgorith algo(GENOME_SIZE, 10);
    //algo.run(10);
    Genome<GENOME_SIZE> *rule = algo.generateGenome();
    string s;
    for(char c: *rule){
        s += c;
    }
    CellulaireAutomaat A(10,10, s);
    //A.changeCell(0, 5, new Road(0, 5, &A));
    A.draw();

    return QApplication::exec();
}
