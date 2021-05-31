

#ifndef TA_CITYSIMULATION_H
#define TA_CITYSIMULATION_H
#include <QApplication>
#include <string>
#include <QTime>
#include "CellulaireAutomaat.h"
#include <iostream>
#include "MainWindow.h"

class CitySimulation {
public:
    float runSimulationGUI(const std::string &rules);
    float runSimulation(const std::string &rules);
    virtual ~CitySimulation();

    CitySimulation();

    /*!
     * runs the simulation for a city with a gui
     * @param width: int width of the city
     * @param height: int height of the city
     * @param rules: the rules for creating the city
     * @return
     * REQUIRE(1 < width, "Width is too small(must be at least 2)!");
     * REQUIRE(1 < height, "Height is too small(must be at least 2)!");
     */
    float runSimulationGUI(int width, int height, const std::string &rules);

    /*!
     *
     * @param width
     * @param height
     * @param rules
     * @return
     * REQUIRE(1 < width, "Width is too small(must be at least 2)!");
     * REQUIRE(1 < height, "Height is too small(must be at least 2)!");
     */
    float runSimulation(int width, int height, const std::string &rules);

private:
    /*!
     * pauzes the simulation for a given time length
     * @param time how long the simulation is pauzes (in micro secs)
     */
    void delay(int time);

    MainWindow* window;
};

#endif //TA_CITYSIMULATION_H
