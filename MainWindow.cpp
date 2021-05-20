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
    for (int i = 2; i < _width - 10; i++) {
        for (int j = 2; j < _height - 10; j++) {
            int random = rand()%1;

            int randomangle = rand()%4;
            if(random == 0){
                /*
                Vegetation* v = new Vegetation(i, j, automaat);
                v->drawToScreen(this);*/
                (*automaat)(i,j).drawToScreen(this);
            }else if(random == 1){
                (*automaat)(i,j).drawToScreen(this);
            }else if(random == 2){
                (*automaat)(i,j).drawToScreen(this);
            }/*else if(random == 3){
                drawTile(i,j,randomangle, "../PixelArt/Road_Rechte_Lijn.png");
            }else if(random == 4){
                drawTile(i,j,randomangle, "../PixelArt/Road_T_Kruispunt.png");
            }else{
                drawTile(i,j,randomangle, "../PixelArt/Road_Kruispunt.png");
            }*/
        }
    }
}

void MainWindow::show() {
    view->show();
}

void MainWindow::clearAll() {
    drawGrid(width, height);
}