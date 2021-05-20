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
    item->setRotation(rot*90);
    rot = rot%4;
    int ofsetx = 0;
    int ofsety = 0;
    if(rot == 1 || rot == 2) {
        ofsetx = 64;
    }
    if(rot == 3 || rot == 2){
        ofsety = 64;
    }
    item->setPos(col*64 + ofsetx ,row*64 + ofsety);
    scene->addItem(item);
}

void MainWindow::addCar(int row, int col, int rot, std::string pixelart){
    QString filename = pixelart.c_str();

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap(filename));
    item->setCacheMode(QGraphicsItem::NoCache);
    qreal scale = qMax(1,1);
    item->setScale(scale);
    item->setRotation(rot*90);
    rot = rot%4;
    int ofsetx = 0;
    int ofsety = 0;
    if(rot == 1 || rot == 2) {
        ofsetx = 64;
    }
    if(rot == 3 || rot == 2){
        ofsety = 64;
    }
    item->setPos(col*64 + ofsetx ,row*64 + ofsety);
    scene->addItem(item);
}

void MainWindow::drawGrid(int _width, int _height) {
    CellulaireAutomaat* automaat = new CellulaireAutomaat(_width, _height, "");

    for (int i = 2; i < _width - 4; i++) {
        for (int j = 2; j < _height - 4; j++) {
            int random = rand()%6;
            int randomangle = rand()%4;
            if(random == 0){

            }else if(random == 1){
                Road* r = new Road(j, i, automaat);
                automaat->changeCell(j, i, r);
            }else if(random == 2){

            }else if(random == 3){

            }else if(random == 4){
                Road* r = new Road(j, i, automaat);
                automaat->changeCell(j, i, r);
            }else{
                Road* r = new Road(j, i, automaat);
                automaat->changeCell(j, i, r);
            }
        }
    }

    for (int i = 2; i < _width - 10; i++) {
        for (int j = 2; j < _height - 10; j++) {
            (*automaat)(i,j)->drawToScreen(this);
        }
    }

    this->drawTile(8, 5, 0, "../PixelArt/Road_Doodlopend.png");
    this->drawTile(8, 6, 1, "../PixelArt/Road_Doodlopend.png");
    this->drawTile(8, 7, 2, "../PixelArt/Road_Doodlopend.png");
    this->drawTile(8, 8, 3, "../PixelArt/Road_Doodlopend.png");
    this->drawTile(8, 9, 4, "../PixelArt/Road_Doodlopend.png");
}

void MainWindow::show() {
    view->show();
}

void MainWindow::clearAll() {
    drawGrid(width, height);
}