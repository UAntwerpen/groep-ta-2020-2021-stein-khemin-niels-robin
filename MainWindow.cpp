//
// Created by Niels on 6/05/2021.
//

#include "MainWindow.h"
#include <QtWidgets>
#include <iostream>
#include <string>

using namespace std;


MainWindow::MainWindow(int w, int h, CellulaireAutomaat *cellulaireAutomaat) {
    width = w;
    height = h;
    c = cellulaireAutomaat;
    scene = new QGraphicsScene();
    addWalls(w, h);
    drawGrid(w, h);
    view = new QGraphicsView(scene);

    QDockWidget *cityDock;
    cityDock = new QDockWidget(tr("City"), this);
    cityDock->setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);
    cityDock->setWidget(view);
    addDockWidget(Qt::RightDockWidgetArea, cityDock);
    view->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);


    QDockWidget *settingsDock;
    settingsDock = new QDockWidget(tr("Settings"), this);
    settingsDock->setAllowedAreas(Qt::LeftDockWidgetArea |
                                 Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, settingsDock);
    settingsDock->setFixedWidth(260);

    QVBoxLayout* boxLayout = new QVBoxLayout();

    QPushButton* button = new QPushButton();
    button->setText("Next day");
    button->setGeometry(30,30,200,50);
    connect(button, &QPushButton::released, this, &MainWindow::temporaryNextDay);
    QPushButton* nextDayBtn = new QPushButton();
    nextDayBtn->setText("Next day");
    nextDayBtn->setGeometry(30,30,200,50);
    connect(nextDayBtn, &QPushButton::released, this, &MainWindow::temporaryNextDay);

    QPushButton* pauseBtn = new QPushButton();
    pauseBtn->setText("Pause");
    pauseBtn->setGeometry(30,80,200,50);
    pauseButton = pauseBtn;
    connect(pauseBtn, &QPushButton::released, this, &MainWindow::pause);


    QPushButton* zoomOutBtn = new QPushButton();
    zoomOutBtn->setText("-");
    zoomOutBtn->setGeometry(30,130,90,50);
    connect(zoomOutBtn, &QPushButton::released, this, &MainWindow::zoomOut);

    QPushButton* zoomInBtn = new QPushButton();
    zoomInBtn->setText("+");
    zoomInBtn->setGeometry(140,130,90,50);
    connect(zoomInBtn, &QPushButton::released, this, &MainWindow::zoomIn);

    settingsDock->layout()->addWidget(nextDayBtn);
    settingsDock->layout()->addWidget(pauseBtn);
    settingsDock->layout()->addWidget(zoomOutBtn);
    settingsDock->layout()->addWidget(zoomInBtn);
}

void MainWindow::temporaryNextDay(){
    cout<<"Button pushed."<<endl;
    c->updateRules();
}

void MainWindow::pause(){
    //TODO pause in CitySimulation.h
    cout<<"Paused"<<endl;
    pauseButton->setText("Resume");
    disconnect(pauseButton, &QPushButton::released, this, &MainWindow::pause);
    connect(pauseButton, &QPushButton::released, this, &MainWindow::resume);
}

void MainWindow::resume(){
    //TODO resume in CitySimulation.h
    cout<<"Resumed"<<endl;
    pauseButton->setText("Pause");
    disconnect(pauseButton, &QPushButton::released, this, &MainWindow::resume);
    connect(pauseButton, &QPushButton::released, this, &MainWindow::pause);
}


void MainWindow::updateRoadUsers() {
    //clearRoadUsers();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            //TODO fix enkel roadusers
            std::pair<int, std::string> pixart = c->operator()(x,y)->getPixelArt();
            drawTile(x,y,pixart.first, pixart.second);
        }
    }
}

void MainWindow::updateAll() {
    //clearBuildings();
    drawGrid(width,height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            std::pair<int, std::string> pixart = (*c)(x,y)->getPixelArt();
            drawTile(x,y,pixart.first, pixart.second);
        }
    }
    updateRoadUsers();
}


void MainWindow::drawTile(int row, int col, int rot, const std::string pixelart) {
    QString filename = pixelart.c_str();
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(filename));
    item->setPixmap(QPixmap(filename));
    item->setCacheMode(QGraphicsItem::NoCache);
    //qreal scale = qMax(zoomTile, zoomTile);
    qreal scale = qMax(2, 2);
    item->setScale(scale);
    item->setRotation(rot * 90);
    rot = rot % 4;
    int ofsetx = 0;
    int ofsety = 0;
    if (rot == 1 || rot == 2) {
        ofsetx = 64;
    }
    if (rot == 3 || rot == 2) {
        ofsety = 64;
    }
    item->setPos(col * 64 + ofsetx, row * 64 + ofsety);
    scene->addItem(item);
    if(pixelart.find("Border") != string::npos){
        Walls.push_back(item);
    } else{
        Buildings.push_back(item);
    }
}

void MainWindow::addCar(int row, int col, int rot, const std::string pixelart) {
    QString filename = pixelart.c_str();
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(filename));
    item->setCacheMode(QGraphicsItem::NoCache);
    qreal scale = qMax(1, 1);
    item->setScale(scale);
    item->setRotation(rot * 90);
    rot = rot % 4;
    int ofsetx = 0;
    int ofsety = 0;
    if (rot == 1 || rot == 2) {
        ofsetx = 64;
    }
    if (rot == 3 || rot == 2) {
        ofsety = 64;
    }
    item->setPos(col * 64 + ofsetx, row * 64 + ofsety);
    scene->addItem(item);
    RoadUsers.push_back(item);
}

void MainWindow::addPedestrian(int row, int col, int rot, const std::string pixelart) {
    QString filename = pixelart.c_str();

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(filename));
    item->setPixmap(QPixmap(filename));
    item->setCacheMode(QGraphicsItem::NoCache);
    qreal scale = qMax(1, 1);
    item->setScale(scale);
    rot = rot % 4;
    int ofsetx = 0;
    int ofsety = 0;
    if (rot == 0 || rot == 1) {
        ofsety = -27;
    }
    if (rot == 1 || rot == 2) {
        ofsetx = 27;
    }
    if (rot == 3 || rot == 2) {
        ofsety = 27;
    }
    if (rot == 0 || rot == 3) {
        ofsetx = -27;
    }
    item->setPos(col * 64 + ofsetx, row * 64 + ofsety);
    scene->addItem(item);
    RoadUsers.push_back(item);
}

void MainWindow::drawGrid(int _width, int _height) {
    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height; j++) {

            drawTile(i, j, 0, "../PixelArt/Default.png");
            /*
            int random = rand() % 14;
            int randomangle = rand() % 4;
            if (random == 0) {
                drawTile(i, j, 0, "../PixelArt/Store.png");
            } else if (random == 1) {
                drawTile(i, j, 0, "../PixelArt/House.png");
            } else if (random == 2) {
                drawTile(i, j, 0, "../PixelArt/Workplace.png");
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
            } else if(random == 9){
                drawTile(i, j, 0, "../PixelArt/House_Broken.png");
            } else if(random == 10){
                drawTile(i, j, 0, "../PixelArt/Store_Broken.png");
            } else if(random == 11){
                drawTile(i, j, 0, "../PixelArt/WorkPlace_Broken.png");
            } else if(random == 12){
                drawTile(i, j, 0, "../PixelArt/Road_Broken.png");
            }  else if(random == 13){
                drawTile(i, j, 0, "../PixelArt/Park_Broken.png");
            }
            */
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

void MainWindow::showView(){
    //view->show();
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

void MainWindow::clearWalls() {
    for (auto it = Walls.begin(); it != Walls.end(); it++) {
        delete *it;
    }
}

MainWindow::~MainWindow() {
    clearBuildings();
    clearRoadUsers();
    clearWalls();
}

void MainWindow::scaleTiles(int zoom) {
    zoomTile = zoom;

    //vervangen door code die elk vak van de cellulaire autmaat opnieuw tekent maar met de nieuwe schaal
    clearBuildings();
    clearRoadUsers();

}

void MainWindow::clicked() {

}

void MainWindow::zoomOut() {
    if(zoomTile <= 0){
        scaleTiles(0);
    }
    else{
        zoomTile--;
        scaleTiles(zoomTile);
    }
}

void MainWindow::zoomIn() {
    zoomTile++;
    scaleTiles(zoomTile);
}
