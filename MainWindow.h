//
// Created by Niels on 6/05/2021.
//

#ifndef TA_MAINWINDOW_H
#define TA_MAINWINDOW_H


#include <QGraphicsScene>
#include <QGraphicsView>
#include "Cell.h"
#include "CellulaireAutomaat.h"

class MainWindow {
public:
    MainWindow(int width, int height);

    void drawTile(int row, int col, int rotation, std::string pixelart);

    void addCar(int row, int col, int rotation, std::string pixelart);

    void show();

    void clearAll();

private:
    void drawGrid(int width, int height);

    std::vector<QGraphicsPixmapItem*> cars;
    QGraphicsScene *scene;
    QGraphicsView *view;
    int width;
    int height;
};

#endif //TA_MAINWINDOW_H
