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
    addWalls(width, height);
    drawGrid(width, height);
    view = new QGraphicsView(scene);
}

void MainWindow::UpdateRoadUsers() {
    clearRoadUsers();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            //todo check pixelart for each cell
        }
    }
}

void MainWindow::UpdateAll() {
    clearBuildings();
    drawGrid(width,height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            //todo check pixelart for each cell
        }
    }
    UpdateRoadUsers();
}


void MainWindow::drawTile(int row, int col, int rot, const std::string pixelart) {
    QString filename = pixelart.c_str();

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(filename));
    item->setCacheMode(QGraphicsItem::NoCache);
    qreal scale = qMax(4, 4);
    item->setScale(scale);
    item->setRotation(rot * 90);
    rot = rot % 4;
    int ofsetx = 0;
    int ofsety = 0;
    if (rot == 1 || rot == 2) {
        ofsetx = 128;
    }
    if (rot == 3 || rot == 2) {
        ofsety = 128;
    }
    item->setPos(col * 128 + ofsetx, row * 128 + ofsety);
    scene->addItem(item);
}

void MainWindow::addCar(int row, int col, int rot, const std::string pixelart) {
    QString filename = pixelart.c_str();

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(filename));
    item->setCacheMode(QGraphicsItem::NoCache);
    qreal scale = qMax(2, 2);
    item->setScale(scale);
    item->setRotation(rot * 90);
    rot = rot % 4;
    int ofsetx = 0;
    int ofsety = 0;
    if (rot == 1 || rot == 2) {
        ofsetx = 128;
    }
    if (rot == 3 || rot == 2) {
        ofsety = 128;
    }
    item->setPos(col * 128 + ofsetx, row * 128 + ofsety);
    scene->addItem(item);
}

void MainWindow::addPedestrian(int row, int col, int rot, const std::string pixelart) {
    QString filename = pixelart.c_str();

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(filename));
    item->setCacheMode(QGraphicsItem::NoCache);
    qreal scale = qMax(2, 2);
    item->setScale(scale);
    rot = rot % 4;
    int ofsetx = 0;
    int ofsety = 0;
    if (rot == 0 || rot == 1) {
        ofsety = -54;
    }
    if (rot == 1 || rot == 2) {
        ofsetx = 54;
    }
    if (rot == 3 || rot == 2) {
        ofsety = 54;
    }
    if (rot == 0 || rot == 3) {
        ofsetx = -54;
    }
    item->setPos(col * 128 + ofsetx, row * 128 + ofsety);
    scene->addItem(item);
}

void MainWindow::drawGrid(int _width, int _height) {
    CellulaireAutomaat *automaat = new CellulaireAutomaat(_width, _height, "");
    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height; j++) {
            int random = rand() % 9;

            int randomangle = rand() % 4;
            if (random == 0) {
                drawTile(i, j, 0, "../PixelArt/Store.png");
                /*
                Vegetation* v = new Vegetation(i, j, automaat);
                v->drawToScreen(this);
                Road* r = new Road(i, j, automaat);
                r->drawToScreen(this);
                 */
            } else if (random == 1) {
                drawTile(i, j, 0, "../PixelArt/House.png");
                //Road* r = new Road(i, j, automaat);
                //r->drawToScreen(this);
            } else if (random == 2) {
                drawTile(i, j, 0, "../PixelArt/Workplace.png");
                //Road* r = new Road(i, j, automaat);
                //r->drawToScreen(this);
            } else if (random == 3) {
                drawTile(i,j,0,"../PixelArt/Park.png");
            } else if (random == 4) {
                drawTile(i, j, randomangle, "../PixelArt/Road_T_Kruispunt.png");
                addPedestrian(i, j, randomangle + 2, "../PixelArt/Pedestrian2.png");
                addCar(i, j, randomangle, "../PixelArt/Car2.png");
            } else if (random == 5) {
                drawTile(i, j, randomangle, "../PixelArt/Road_Kruispunt.png");
                addPedestrian(i, j, randomangle + 2, "../PixelArt/Pedestrian3.png");
                addCar(i, j, randomangle, "../PixelArt/Car3.png");
            } else if (random == 6) {
                drawTile(i, j, randomangle, "../PixelArt/Road_Doodlopend.png");
                addPedestrian(i, j, randomangle + 2, "../PixelArt/Pedestrian1.png");
                addCar(i, j, randomangle + 2, "../PixelArt/Car2.png");
            } else if(random == 7) {
                drawTile(i, j, randomangle, "../PixelArt/Road_Bocht.png");
                addPedestrian(i, j, randomangle + 2, "../PixelArt/Pedestrian2.png");
                addCar(i, j, randomangle + 2, "../PixelArt/Car2.png");
            } else if(random == 8){
                drawTile(i, j, randomangle, "../PixelArt/Road_Recht.png");
                addPedestrian(i, j, randomangle + 2, "../PixelArt/Pedestrian1.png");
                addCar(i, j, randomangle, "../PixelArt/Car1.png");
            }
        }
    }
}

void MainWindow::addWalls(int _width, int _height){
    drawTile(-1,-1, 0, "../PixelArt/Border_hoek.png");
    drawTile(-1,_width, 1, "../PixelArt/Border_hoek.png");
    drawTile(_height,_width, 2, "../PixelArt/Border_hoek.png");
    drawTile(_height,-1, 3, "../PixelArt/Border_hoek.png");
    for(int  i = 0; i < _width; i++){
        drawTile(-1,i, 0, "../PixelArt/Border_lang.png");
        drawTile(_height,i, 2, "../PixelArt/Border_lang.png");
    }
    for(int  i = 0; i < _height; i++){
        drawTile(i,-1, 3, "../PixelArt/Border_lang.png");
        drawTile(i,_width, 1, "../PixelArt/Border_lang.png");
    }
}

void MainWindow::show() {
    view->show();
}

void MainWindow::clearBuildings() {
    for (auto it = Buildings.begin(); it != Buildings.end(); it++) {
        delete *it;
    }
}

void MainWindow::clearRoadUsers() {
    for (auto it = RoadUsers.begin(); it != RoadUsers.end(); it++) {
        delete *it;
    }
}

MainWindow::~MainWindow() {
    clearBuildings();
    clearRoadUsers();
}
