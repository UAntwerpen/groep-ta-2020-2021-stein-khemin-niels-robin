//
// Created by Niels on 6/05/2021.
//

#include "MainWindow.h"
#include <string>
#include "lib/DesignByContract.h"
#include "Vehicle.h"
#include "Citizen.h"

using namespace std;


MainWindow::MainWindow(int w, int h, CellulaireAutomaat *cellulaireAutomaat) {
    REQUIRE(1 < w, "Width is too small(must be at least 2)!");
    REQUIRE(1 < h, "Height is too small(must be at least 2)!");
    width = w;
    height = h;
    c = cellulaireAutomaat;
    scene = new QGraphicsScene();
    drawGrid(w, h);
    view = new QGraphicsView(scene);

    cityDock = new QDockWidget(tr("City"), this);
    cityDock->setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);
    cityDock->setWidget(view);
    addDockWidget(Qt::RightDockWidgetArea, cityDock);
    view->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
    view->setBackgroundBrush(QColor("#4CAF50"));

    QDockWidget *settingsDock;
    settingsDock = new QDockWidget(tr("Settings"), this);
    settingsDock->setAllowedAreas(Qt::LeftDockWidgetArea |
                                 Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, settingsDock);
    settingsDock->setFixedWidth(260);

    QLabel* daytext = new QLabel("day: 0");
    daytext->setGeometry(30,30,200,50);
    dayint = 0;
    day = daytext;

    QPushButton* pauseBtn = new QPushButton();
    pauseBtn->setText("Pause");
    pauseBtn->setGeometry(30,80,200,50);
    pauseButton = pauseBtn;
    connect(pauseBtn, &QPushButton::released, this, &MainWindow::pressedPause);


    QPushButton* zoomOutBtn = new QPushButton();
    zoomOutBtn->setText("-");
    zoomOutBtn->setGeometry(30,140,90,50);
    connect(zoomOutBtn, &QPushButton::released, this, &MainWindow::zoomOut);

    QPushButton* zoomInBtn = new QPushButton();
    zoomInBtn->setText("+");
    zoomInBtn->setGeometry(140,140,90,50);
    connect(zoomInBtn, &QPushButton::released, this, &MainWindow::zoomIn);

    QSlider* slider = new QSlider(Qt::Horizontal);
    slider->setGeometry(30, 200, 200, 30);
    slider->setMinimum(1);
    slider->setMaximum(20);
    slider->setValue(6);
    dayLength = slider;

    settingsDock->layout()->addWidget(daytext);
    settingsDock->layout()->addWidget(pauseBtn);
    settingsDock->layout()->addWidget(zoomOutBtn);
    settingsDock->layout()->addWidget(zoomInBtn);
    settingsDock->layout()->addWidget(slider);
}

void MainWindow::updateVehicles() {
    clearVehicles();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Cell *cell = (*c)(x,y);

            if (cell->getState() == EResidentialZone) {
                Vehicle* car = cell->getCar();
                pair<int, int> carPos = car->getLocation()->getPos();
                // enkel auto afbeelden als die onderweg is.
                if (car->getStatus()){
                    addVehicle(carPos.first, carPos.second, getRotation(car->getDirection()), car->getPixelart());
                }
            }
        }
    }
}

void MainWindow::updatePedestrians() {
    clearPedestrians();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Cell *cell = (*c)(x,y);
            if (cell->getState() == EResidentialZone) {
                vector<Citizen*> citizens = cell->getPersons();
                for(auto it = citizens.begin(); it != citizens.end(); it++){
                    pair<int, int> pedestrianPos = (*it)->getLocation()->getPos();
                    if((*it)->getStatus()){
                        addPedestrian(pedestrianPos.first, pedestrianPos.second, getRotation((*it)->getDirection()), (*it)->getPixelart());
                    }
                }
            }
        }
    }
}

void MainWindow::moveVehicles(){
    for(auto it = vehicles.begin(); it != vehicles.end(); it++){
        QGraphicsPixmapItem* vehicle = (*it);
        int rot = vehicle->rotation();
        if(rot == 0){
            vehicle->setY(vehicle->y()-(zoomTile*4));
        }
        else if(rot == 90){
            vehicle->setX(vehicle->x()+(zoomTile*4));
        }
        else if(rot == 180){
            vehicle->setY(vehicle->y()+(zoomTile*4));
        }
        else if(rot == 270){
            vehicle->setX(vehicle->x()-(zoomTile*4));
        }
    }
}

void MainWindow::movePedestrians(){
    for(auto it = pedestrians.begin(); it != pedestrians.end(); it++) {
        QGraphicsPixmapItem *pedestrian = it->first;
        int rot = it->second;
        if(rot == 0){
            pedestrian->setY(pedestrian->y()-(zoomTile));
        }
        else if(rot == 1){
            pedestrian->setX(pedestrian->x()+(zoomTile));
        }
        else if(rot == 2){
            pedestrian->setY(pedestrian->y()+(zoomTile));
        }
        else if(rot == 3){
            pedestrian->setX(pedestrian->x()-(zoomTile));
        }
    }
}

int MainWindow::getRotation(char direction){
    switch(direction){
        case('N'):
            return 0;
        case('E'):
            return 1;
        case('S'):
            return 2;
        case('W'):
            return 3;
        default:
            return 0;
    }
};

void MainWindow::updateAll() {
    clearWalls();
    clearBuildings();
    drawGrid(width,height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            std::pair<int, std::string> pixart = (*c)(x,y)->getPixelArt();
            drawTile(x,y,pixart.first, pixart.second);
        }
    }
    updateVehicles();
    updatePedestrians();
}

void MainWindow::addDay() {
    dayint++;
    string str = "day: "+ to_string(dayint);
    QString time = QString::fromStdString(str);
    day->setText(time);
}

bool MainWindow::getPause(){
    return pause;
}

MainWindow::~MainWindow() {
    clearBuildings();
    clearVehicles();
    clearPedestrians();
    clearWalls();
}

void MainWindow::drawTile(int row, int col, int rot, const std::string& pixelart) {
    QString filename = pixelart.c_str();
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(filename));
    item->setPixmap(QPixmap(filename));
    item->setCacheMode(QGraphicsItem::NoCache);
    qreal scale = qMax(zoomTile, zoomTile);
    item->setScale(scale);
    item->setRotation(rot * 90);
    rot = rot % 4;
    int ofsetx = 0;
    int ofsety = 0;
    if (rot == 1 || rot == 2) {
        ofsetx = zoomTile*32;
    }
    if (rot == 3 || rot == 2) {
        ofsety = zoomTile*32;
    }
    item->setPos(col * (32*zoomTile) + ofsetx, row * (32*zoomTile) + ofsety);
    scene->addItem(item);
    if(pixelart.find("Border") != string::npos){
        walls.push_back(item);
    } else{
        buildings.push_back(item);
    }
}

void MainWindow::addVehicle(int row, int col, int rot, const std::string& pixelart) {
    REQUIRE(0 <= row && row < height, "Row with is out of bounds!");
    REQUIRE(0 <= col && col < width, "Column is out of bounds!");
    QString filename = pixelart.c_str();
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(filename));
    item->setCacheMode(QGraphicsItem::NoCache);
    qreal scale = qMax(zoomTile/2, zoomTile/2);
    item->setScale(scale);
    rot = rot % 4;
    item->setRotation(rot * 90);
    int ofsetx = 0;
    int ofsety = 0;
    if (rot == 1 || rot == 2) {
        ofsetx = zoomTile*32;
    }
    if (rot == 3 || rot == 2) {
        ofsety = zoomTile*32;
    }
    item->setPos(col * (32*zoomTile) + ofsetx, row * (32*zoomTile) + ofsety);
    scene->addItem(item);
    vehicles.push_back(item);
}

void MainWindow::addPedestrian(int row, int col, int rot, const std::string& pixelart) {
    REQUIRE(0 <= row && row < height, "Row with is out of bounds!");
    REQUIRE(0 <= col && col < width, "Column is out of bounds!");
    QString filename = pixelart.c_str();

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(filename));
    item->setPixmap(QPixmap(filename));
    item->setCacheMode(QGraphicsItem::NoCache);
    qreal scale = qMax(zoomTile/2, zoomTile/2);
    item->setScale(scale);
    rot = rot % 4;
    int ofsetx = 0;
    int ofsety = 0;
    if (rot == 0 || rot == 1) {
        ofsety = -27*(zoomTile/2);
    }
    if (rot == 1 || rot == 2) {
        ofsetx = 27*(zoomTile/2);
    }
    if (rot == 3 || rot == 2) {
        ofsety = 27*(zoomTile/2);
    }
    if (rot == 0 || rot == 3) {
        ofsetx = -27*(zoomTile/2);
    }
    item->setPos(col * (32*zoomTile) + ofsetx, row * (32*zoomTile) + ofsety);
    scene->addItem(item);
    pedestrians.push_back(make_pair(item,rot));
}

void MainWindow::pressedPause(){
    pause = true;
    pauseButton->setText("Resume");
    disconnect(pauseButton, &QPushButton::released, this, &MainWindow::pressedPause);
    connect(pauseButton, &QPushButton::released, this, &MainWindow::pressedResume);
}

void MainWindow::pressedResume(){
    pause = false;
    pauseButton->setText("Pause");
    disconnect(pauseButton, &QPushButton::released, this, &MainWindow::pressedResume);
    connect(pauseButton, &QPushButton::released, this, &MainWindow::pressedPause);
}

void MainWindow::clearBuildings() {
    for (auto it = buildings.begin(); it != buildings.end(); it++) {
        delete *it;
    }
    buildings = {};
}

void MainWindow::clearVehicles() {
    for (auto it = vehicles.begin(); it != vehicles.end(); it++) {
        delete *it;
    }
    vehicles = {};
}

void MainWindow::clearPedestrians(){
    for (auto it = pedestrians.begin(); it != pedestrians.end(); it++) {
        delete it->first;
    }
    pedestrians = {};
}

void MainWindow::clearWalls() {
    for (auto it = walls.begin(); it != walls.end(); it++) {
        delete *it;
    }
    walls = {};
}

void MainWindow::zoomOut() {
    zoomTile/=2;
    updateAll();
}

void MainWindow::zoomIn() {
    zoomTile*=2;
    updateAll();
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

void MainWindow::drawGrid(int _width, int _height) {
    addWalls(_width, _height);
    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height; j++) {
            drawTile(i, j, 0, "../PixelArt/Park.png");
        }
    }
}

void MainWindow::pauseSimulation() {
    pressedPause();
}

void MainWindow::resumeSimulation() {
    pressedResume();
}

void MainWindow::setDayOrNight(int a) {
    view->setForegroundBrush(QBrush(QColor(0, 0, 70, a)));
}

int MainWindow::getDayLengthValue(){
    return dayLength->value();
}





