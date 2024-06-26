#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // generate a random deviceID which is a 6-digit number
    deviceID = QRandomGenerator::global()->bounded(1000000);
    // create two canvas
    canvas = new Canvas(this, deviceID);
    receiveCanvas = new ReceiveCanvas(this, deviceID);
    QWidget *centralWidget = new QWidget(this);
    auto *layout = new QHBoxLayout(centralWidget);
    layout->addWidget(canvas);
    layout->addWidget(receiveCanvas);
    this->setCentralWidget(centralWidget);

    // create menubar
    QMenuBar *menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);
    QMenu *colorMenu = new QMenu("Colors", this);
    QMenu *width = new QMenu("Width", this);
    QMenu *penMenu = new QMenu("Pen", this);
    menuBar->addMenu(colorMenu);
    menuBar->addMenu(width);
    menuBar->addMenu(penMenu);

    // add width actions
    for (int i = 1; i <= 10; i++) {
        QAction *action = new QAction(QString::number(i), this);
        width->addAction(action);
        connect(action, &QAction::triggered, [=]() {
            canvas->setPenWidth(i);
        });
    }

    // colorMenu
    // add color actions
    for (auto &pair: colorNames) {
        QAction *action = new QAction(pair.second.c_str(), this);
        colorMenu->addAction(action);
        connect(action, &QAction::triggered, [=]() {
            penColor = pair.first;
            canvas->setPenColor(penColor);
        });
    }

    // penMenu
    QAction *freeAction = new QAction("Free", this);
    QAction *lineAction = new QAction("Line", this);
    QAction *rectAction = new QAction("Rect", this);
    QAction *ellipseAction = new QAction("Ellipse", this);
    QAction *clearAction = new QAction("Clear", this);
    penMenu->addAction(freeAction);
    penMenu->addAction(lineAction);
    penMenu->addAction(rectAction);
    penMenu->addAction(ellipseAction);
    penMenu->addAction(clearAction);

    connect(freeAction, &QAction::triggered, [=]() {
        canvas->penType = DrawingCommandType::Free;
    });

    connect(lineAction, &QAction::triggered, [=]() {
        canvas->penType = DrawingCommandType::Line;
    });

    connect(rectAction, &QAction::triggered, [=]() {
        canvas->penType = DrawingCommandType::Rect;
    });

    connect(ellipseAction, &QAction::triggered, [=]() {
        canvas->penType = DrawingCommandType::Ellipse;
    });

    connect(clearAction, &QAction::triggered, [=]() {
        canvas->clear();
    });

    // create threads
    std::cout << "create sendThread" << std::endl;
    sendThread = new SendThread(deviceID, commandQueue);
    std::cout << "create receivedThread" << std::endl;
    receivedThread = new ReceivedThread(deviceID, commandQueue, receiveCanvas);

    connect(canvas,&Canvas::commandFinished,sendThread,&SendThread::sendSlot);
    connect(receivedThread, &ReceivedThread::commandReceived, receiveCanvas, &ReceiveCanvas::receiveCommand);

    sendThread->start();
    receivedThread->start();
}

MainWindow::~MainWindow() {
    delete ui;
    delete canvas;
    delete receiveCanvas;
}
