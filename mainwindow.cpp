#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector>
#include <unordered_map>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include "colors.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    canvas = new Canvas(this);
    receiveCanvas = new ReceiveCanvas(this);

    QWidget *centralWidget = new QWidget(this);
    auto *layout = new QHBoxLayout(centralWidget);
    layout->addWidget(canvas);
    layout->addWidget(receiveCanvas);
    this->setCentralWidget(centralWidget);

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *colorMenu = new QMenu("Colors", this);
    QMenu *clearMenu = new QMenu("Tools", this);
    QAction *clearAction = new QAction("Clear", this);
    connect(clearAction, &QAction::triggered, [=]() {
        canvas->clear();
    });
    clearMenu->addAction(clearAction);

    // add color actions
    for (auto &pair: colorNames) {
        QAction *action = new QAction(pair.second.c_str(), this);
        colorMenu->addAction(action);
        connect(action, &QAction::triggered, [=]() {
            penColor = pair.first;
            canvas->penColor = penColor;
        });
    }

    menuBar->addMenu(colorMenu);
    menuBar->addMenu(clearMenu);
    this->setMenuBar(menuBar);
}

MainWindow::~MainWindow() {
    delete ui;
}
