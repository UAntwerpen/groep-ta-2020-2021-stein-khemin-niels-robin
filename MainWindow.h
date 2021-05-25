//
// Created by Niels on 6/05/2021.
//

#ifndef TA_MAINWINDOW_H
#define TA_MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtWidgets>
#include "Cell.h"
#include "CellulaireAutomaat.h"

class MainWindow: public QMainWindow {
public:
    MainWindow(int width, int height, CellulaireAutomaat *cellulaireAutomaat);

    void UpdateRoadUsers();

    void UpdateAll();

    virtual ~MainWindow();

    void showView();

    //private maken
    void drawTile(int row, int col, int rotation, const std::string pixelart);
    void addCar(int row, int col, int rotation, const std::string pixelart);
    void addPedestrian(int row, int col, int rotation, const std::string pixelart);
    void TemporaryNextDay();
    void pause();
    void resume();
private slots:
    void clicked();
private:

    void clearRoadUsers();
    void clearBuildings();
    void clearWalls();

    void addWalls(int width, int height);

    //TODO weg doen
    void drawGrid(int width, int height);

    CellulaireAutomaat* c;
    std::vector<QGraphicsPixmapItem*> RoadUsers;
    std::vector<QGraphicsPixmapItem*> Buildings;
    std::vector<QGraphicsPixmapItem*> Walls;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QVBoxLayout* boxLayout;
    QPushButton* button;
    QDockWidget* cityDock;
    int height;
    int width;
    QPushButton* pauseButton;
};

#endif //TA_MAINWINDOW_H
