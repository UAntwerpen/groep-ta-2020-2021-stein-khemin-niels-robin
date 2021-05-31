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
     * update alle wegggebruikers
     */
    void updateVehicles();

    void updatePedestrians();

    void moveCars();

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

private:
    int getRotation(char direction);

    /*!
     * kleurt een cell in op het scherm
     * @param row: rij positie
     * @param col: kolom positie
     * @param rotation: geeft hoeveel graden de afbeelding gedraaid moet worden
     * @param pixelart: verwijzing naar afbeelding
     */
    void drawTile(int row, int col, int rotation, const std::string pixelart);

    /*!
     * plaatst een auto op de weg
     * @param row: rij positie
     * @param col: kolom positie
     * @param rotation: geeft hoeveel graden de afbeelding gedraaid moet worden
     * @param pixelart: verwijzing naar afbeelding
     */
    void addCar(int row, int col, int rotation, const std::string pixelart);

    /*!
     * plaatste een voetganger op de weg
     * @param row: rij positie
     * @param col: kolom positie
     * @param rotation: geeft hoeveel graden de afbeelding gedraaid moet worden
     * @param pixelart: verwijzing naar afbeelding
     */
    void addPedestrian(int row, int col, int rotation, const std::string pixelart);

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