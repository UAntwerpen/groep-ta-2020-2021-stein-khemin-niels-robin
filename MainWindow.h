//
// Created by Niels on 6/05/2021.
//

#ifndef TA_MAINWINDOW_H
#define TA_MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtWidgets>
#include <utility>
#include "Cell.h"
#include "CellulaireAutomaat.h"

class MainWindow: public QMainWindow {
public:
    /*!
     * initialiseert de mainwindow
     * @param width: breedte van de cell
     * @param height: hoogte van de cell
     * @param CellulaireAutomaat:automaat die mainwindow bestuurt
     * REQUIRE(1 < width, "Width is too small(must be at least 2)!");
     * REQUIRE(1 < height, "Height is too small(must be at least 2)!");
     */
    MainWindow(int width, int height, CellulaireAutomaat *cellulaireAutomaat);

    /*!
     * update alle voertuigen
     */
    void updateVehicles();

    /*!
     * update alle voetgangers
     */
    void updatePedestrians();

    /*!
     * zet voertuigen vooruit
     */
    void moveVehicles();

    /*!
     * zet voetganger vooruit
     */
    void movePedestrians();

    /*!
     * update de stad
     */
    void updateAll();

    /*!
     * voegt een dag toe aan de counter
     */
    void addDay();

    /*!
     * geeft weer of de simulatie gepauseerd moet worden of niet
     * @return pause: true als het gepauseerd is, false als het niet gepauseerd is
     */
    bool getPause();

    /*!
     * destructor
     */
    virtual ~MainWindow();

    /*!
     * Pause simulation
     */
    void pauseSimulation();

    /*!
     * Resume simulation
     */
    void resumeSimulation();

    /*!
     * maakt view donker of lichter
     */
    void setDayOrNight(int transparent);

    /*!
     * geeft lengte van stad terug
     */
    int getDayLengthValue();

private:
    /*!
     * geeft rotatie van voetganger terug
     */
    int getRotation(char direction);

    /*!
     * kleurt een cell in op het scherm
     * @param row: rij positie
     * @param col: kolom positie
     * @param rotation: geeft hoeveel graden de afbeelding gedraaid moet worden
     * @param pixelart: verwijzing naar afbeelding
     * REQUIRE(0 <= row && row < height, "Row with is out of bounds!");
     * REQUIRE(0 <= col && col < width, "Column is out of bounds!");
     */
    void drawTile(int row, int col, int rotation, const std::string& pixelart);

    /*!
     * plaatst een auto op de weg
     * @param row: rij positie
     * @param col: kolom positie
     * @param rotation: geeft hoeveel graden de afbeelding gedraaid moet worden
     * @param pixelart: verwijzing naar afbeelding
     * REQUIRE(0 <= row && row < height, "Row with is out of bounds!");
     * REQUIRE(0 <= col && col < width, "Column is out of bounds!");
     */
    void addVehicle(int row, int col, int rotation, const std::string& pixelart);

    /*!
     * plaatste een voetganger op de weg
     * @param row: rij positie
     * @param col: kolom positie
     * @param rotation: geeft hoeveel graden de afbeelding gedraaid moet worden
     * @param pixelart: verwijzing naar afbeelding
     * REQUIRE(0 <= row && row < height, "Row with is out of bounds!");
     * REQUIRE(0 <= col && col < width, "Column is out of bounds!");
     */
    void addPedestrian(int row, int col, int rotation, const std::string& pixelart);

    /*!
     * functie die wordt aangeroepen als er op de pauseknop wordt gedrukt, zet variabele pause op true
     */
    void pressedPause();

    /*!
     * functie die wordt aangeroepen als er op de pauseknop wordt gedrukt, zet variabele pause op false
     */
    void pressedResume();

    /*!
     * verwijdert alle weggebruikers
     */
    void clearVehicles();

    /*!
     * verwijdert alle voetgangers
     */
    void clearPedestrians();

    /*!
     * verwijdert alle gebouwen/wegen
     */
    void clearBuildings();

    /*!
     * verwijdert de muren rond te stad
     */
    void clearWalls();

    /*!
     * functie die wordt aangeroepen als er op de -knop wordt gedrukt, zet variabele zoom -1
     */
    void zoomOut();

    /*!
     * functie die wordt aangeroepen als er op de +knop wordt gedrukt, zet variabele zoom +1
     */
    void zoomIn();

    /*!
     * voegt muren toe aan de stad
     */
    void addWalls(int width, int height);

    /*!
     * zet alle cellen op default afbeeldingen
     */
    void drawGrid(int width, int height);

    CellulaireAutomaat* c;
    std::vector<std::pair<QGraphicsPixmapItem*,int>> pedestrians;
    std::vector<QGraphicsPixmapItem*> vehicles;
    std::vector<QGraphicsPixmapItem*> buildings;
    std::vector<QGraphicsPixmapItem*> walls;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QVBoxLayout* boxLayout;
    QPushButton* button;
    QSlider* dayLength;
    QDockWidget* cityDock;
    int height;
    int width;
    double zoomTile = 2;
    QPushButton* pauseButton;
    QLabel* day;
    int dayint;
    bool pause = false;
};

#endif //TA_MAINWINDOW_H