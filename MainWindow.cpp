//
// Created by Niels on 6/05/2021.
//

#include "MainWindow.h"
#include <QtWidgets>
#include <string>
using namespace std;

MainWindow::MainWindow(int w, int h) {
    width = w;
    height = h;
    scene = new QGraphicsScene();
    drawGrid(width, height);
    view = new QGraphicsView(scene);
}

void MainWindow::drawTile(int row, int col, std::string pixelart){
    QString filename;
    for(int i = 0; i<pixelart.size(); i++){
        filename+=pixelart[i];
    }
    QGraphicsPixmapItem* item=new QGraphicsPixmapItem(QPixmap(filename));
    item->setCacheMode(QGraphicsItem::NoCache);
    qreal scale = qMax(4,4);
    item->setScale(scale);
    scene->addItem(item);
    item->setPos(row*64,col*64);
}

void MainWindow::drawGrid(int width, int height) {
    for(int i=0; i<width; i++)
    {
        for(int j=0; j<height; j++)
        {
            drawTile(i,j, "../PixelArt/Default.png");
        }
    }
}

void MainWindow::show(){
    view->show();
}

void MainWindow::clearAll(){
    drawGrid(width, height);
}