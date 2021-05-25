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
    /*MainWindow w(100,100);
    w.show();
    w.showView();
    */
    GeneticAlgorith algo(GENOME_SIZE, 10);
    //algo.run(10);
    Genome<GENOME_SIZE> *rule = algo.generateGenome();
    string s;
    for(char c: *rule){
        s += c;
    }
    CellulaireAutomaat A(100,100, s);

    return QApplication::exec();
}
