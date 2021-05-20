//
// Created by Niels on 6/05/2021.
//

#include "MainWindow.h"
#include <QtWidgets>
#include <iostream>
#include <string>

using namespace std;

MainWindow::MainWindow(int w, int h) {
    width = w;
    height = h;
    scene = new QGraphicsScene();
    drawGrid(width, height);
    view = new QGraphicsView(scene);
}

void MainWindow::drawTile(int row, int col, int rot, std::string pixelart){
    QString filename = pixelart.c_str();

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(filename));
    item->setCacheMode(QGraphicsItem::NoCache);
    qreal scale = qMax(2,2);
    item->setScale(scale);
    //std::cout<<rot<<std::endl;
    item->setRotation(rot*90);
    int ofsetx = 0;
    int ofsety = 0;
    if(rot == 1 || rot == 2) {
        ofsetx = 64;
    }
    if(rot == 3 || rot == 2){
        ofsety = 64;
    }
    item->setPos(row*64 + ofsetx ,col*64 + ofsety);
    scene->addItem(item);
}

void MainWindow::drawGrid(int _width, int _height) {
    CellulaireAutomaat* automaat = new CellulaireAutomaat(_width, _height, "");

    Road* r = new Road(10, 10, automaat);
    automaat->changeCell(10, 10, r);

    Road* r2 = new Road(10, 11, automaat);
    automaat->changeCell(10, 11, r2);

    Road* r3 = new Road(10, 12, automaat);
    automaat->changeCell(10, 12, r3);


    for (int i = 2; i < _width - 10; i++) {
        for (int j = 2; j < _height - 10; j++) {
            (*automaat)(i,j).drawToScreen(this);
        }
    }
}

void MainWindow::show() {
    view->show();
}

void MainWindow::clearAll() {
    drawGrid(width, height);
}