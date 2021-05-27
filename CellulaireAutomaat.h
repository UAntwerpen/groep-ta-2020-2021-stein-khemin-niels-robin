#ifndef TA_CELLULAIREAUTOMAAT_H
#define TA_CELLULAIREAUTOMAAT_H

#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>

#include "Cell.h"
#include "MainWindow.h"

class CellulaireAutomaat {
public:
    /*!
     * initialiseert de cell
     * @param width breedt van de cell
     * @param height hoogte van de cell
     * REQUIRE(1 < width, "Width is too small(must be at least 2)!");
     * REQUIRE(1 < height, "Height is too small(must be at least 2)!");
     */
    CellulaireAutomaat(int width, int height, const std::string& rules, bool qt = true);

    CellulaireAutomaat(const std::string& filename);

    virtual ~CellulaireAutomaat();

    /*!
     * geeft de cell op rij kolom terug
     * @param row rij van de cell
     * @param column kolom can de cell
     * @return reference van de cell
     */
    Cell* operator()(int row, int column) const;

    /*!
     * geeft de neighbourhood van een cell terug
     * @param row rij van de cell
     * @param col kolom van de cell
     * @return geeft een vector van de cellen terug van linksboven in klokwijze manier
     * REQUIRE(0 <= row && row < width, "Row is out of bounds!");
     * REQUIRE(0 <= column && column < height, "Column is out of bounds!");
     */
    std::vector<Cell*> getNeighbourhood(int row, int col);

    /*!
     * veranderd de cell naar een nieuwe cell
     * @param row rij van de cell
     * @param column kolom van de cell
     * @param to Cell* in wat de cell verandert wordt
     * REQUIRE(0 <= row && row < width, "Row is out of bounds!");
     * REQUIRE(0 <= column && column < height, "Column is out of bounds!");
     * REQUIRE(to != nullptr, "De gegeven cell is een nullptr!");
     */
    void changeCell(int row, int column, Cell* to);

    /*!
     * applies the rules in the automat from top left to bottom right
     */
    void updateRules();

    /*!
     * updates every cell in the automat from top left to bottom right
     */
    void updateCells();

    /*!
     * gives back how many states of the given state are in the automat
     * @param state to be counted
     * @return int
     */
    int count(const EStates& state) const;

    /*!
     * gives back how many states of the given state are in the given radius
     * @param state type dat geteld moet worden
     * @param row rij waaruit geteld moet worden
     * @param col kolom waaruit geteld moet worden
     * @param radius straal die bepaald hoeveel cellen worden negekijken
     * @return int
     */
    int count(const EStates& state, int row, int col, int radius) const;

    /*!
     * counts every type
     * @return how many times every type occurs
     */
    std::map<EStates, int> count_all() const;

    /*!
     * returns width of the automat
     * @return int
     */
    int getWidth() const;

    /*!
     * returns height of the automat
     * @return int
     * \n ENSURE(height > 0, "Height is less then 0!");
     */
    int getHeight() const;

    /*!
     * tekent de automaat op het scherm
     */
    void draw();

    /*!
     * adds a main street that can't be changed
     * @param row int
     * @param col int
     */
    void addMainStreet(int row, int col);

    /*!
     * @return returns the score of the city
     */
    float getScore() const;

private:
    /*!
    * geeft de neighbourhood van een cell terug
    * @param row rij van de cell
    * @param col kolom van de cell
    * @return geeft een vector van de cellen terug van linksboven in klokwijze manier
    * REQUIRE(0 <= row && row < width, "Row is out of bounds!");
    * REQUIRE(0 <= column && column < height, "Column is out of bounds!");
    */
    int getNeighbourhoodValue(int row, int col);

    /*!
    * geeft de neighbourhood van een cell terug
    * @param row rij van de cell
    * @param col kolom van de cell
     * @param map: map van de Estates
    * @return geeft een vector van de cellen terug van linksboven in klokwijze manier
    * REQUIRE(0 <= row && row < width, "Row is out of bounds!");
    * REQUIRE(0 <= column && column < height, "Column is out of bounds!");
    */
    static int getNeighbourhoodValue(int row, int col, const std::vector<std::vector<EStates>>& map);

    int width;
    int height;
    std::vector<Cell*> matrix;
    std::string rules;
    MainWindow* w;
    std::pair<int, int> main_street;
    bool qt;
};

#endif //TA_CELLULAIREAUTOMAAT_H
