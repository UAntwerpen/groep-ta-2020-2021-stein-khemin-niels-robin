//
// Created by Niels on 6/05/2021.
//

#ifndef TA_MAINWINDOW_H
#define TA_MAINWINDOW_H

#include <string>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtWidgets>
#include "Cell.h"
#include "CellulaireAutomaat.h"

class MainWindow: public QMainWindow {
public:
    MainWindow(int width, int height, CellulaireAutomaat *cellulaireAutomaat);

    void updateRoadUsers();

    void updateAll();

    void addDay();

    virtual ~MainWindow();



    //private maken
    void drawTile(int row, int col, int rotation, const std::string pixelart);
    void addCar(int row, int col, int rotation, const std::string pixelart);
    void addPedestrian(int row, int col, int rotation, const std::string pixelart);
    void temporaryNextDay();
    void pause();
    void resume();
private slots:
    void clicked();
private:

    void clearRoadUsers();
    void clearBuildings();
    void clearWalls();

    void zoomOut();
    void zoomIn();

    void addWalls(int width, int height);

    //TODO weg doen
    void drawGrid(int width, int height);

    CellulaireAutomaat* c;
    std::vector<QGraphicsPixmapItem*> roadUsers;
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
};

#endif //TA_MAINWINDOW_H
