#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector>
#include <unordered_map>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include "colors.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    canvas = new Canvas(this);
    this->setCentralWidget(canvas);

//    QMenuBar *menuBar= new QMenuBar(this);
////    QMenu *colorMenu= menuBar->addMenu("Color");
//    menuBar->addMenu("Color");

    // 创建菜单栏
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *colorMenu = new QMenu("Colors", this);
    QMenu *clearMenu = new QMenu("Clear", this);
    clearMenu->addAction("Clear");
    clearMenu->addAction("Eraser");

    for (auto &pair: colorNames) {
        colorMenu->addAction(new QAction(pair.second.c_str(), this));
    }
}

    menuBar->addMenu(colorMenu);
    menuBar->addMenu(clearMenu);
    this->setMenuBar(menuBar);

    // 创建状态栏
    QStatusBar *statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setBlack() {

}

void MainWindow::setRed() {

}

void MainWindow::setGreen() {

}

void MainWindow::setBlue() {

}

void MainWindow::setYellow() {

}

void MainWindow::setWhite() {

}

void MainWindow::setCyan() {

}

void MainWindow::setMagenta() {

}

void MainWindow::setClear() {

}

void MainWindow::setEraser() {

}
