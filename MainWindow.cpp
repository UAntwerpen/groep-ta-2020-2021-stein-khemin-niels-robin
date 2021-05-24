//
// Created by Niels on 6/05/2021.
//

#include "MainWindow.h"
#include <iostream>
#include <string>

using namespace std;


MainWindow::MainWindow(int w, int h) {
    width = w;
    height = h;
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
    connect(button, &QPushButton::released, this, &MainWindow::TemporaryNextDay);

    QPushButton* button1 = new QPushButton();
    button1->setText("Pause");
    button1->setGeometry(30,80,200,50);
    pauseButton = button1;
    connect(button1, &QPushButton::released, this, &MainWindow::pause);

    settingsDock->layout()->addWidget(button);
    settingsDock->layout()->addWidget(button1);
}

void MainWindow::TemporaryNextDay(){
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


void MainWindow::UpdateRoadUsers() {
    clearRoadUsers();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            //TODO fix enkel roadusers
            std::pair<int, std::string> pixart = c->operator()(x,y)->getPixelArt();
            drawTile(x,y,pixart.first, pixart.second);
        }
    }
}

void MainWindow::UpdateAll() {
    clearBuildings();
    drawGrid(width,height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            std::pair<int, std::string> pixart = c->operator()(x,y)->getPixelArt();
            drawTile(x,y,pixart.first, pixart.second);
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
    RoadUsers.push_back(item);
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
    RoadUsers.push_back(item);
}

void MainWindow::drawGrid(int _width, int _height) {
    CellulaireAutomaat *automaat = new CellulaireAutomaat(_width, _height, "");
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
