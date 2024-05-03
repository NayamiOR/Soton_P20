#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QRandomGenerator>

#include <random>
#include <vector>
#include <unordered_map>

#include "Canvas.h"
#include "SafeQueue.h"
#include "ReceiveCanvas.h"
#include "colors.h"
#include "DrawingCommand.h"
#include "SendThread.h"
#include "ReceivedThread.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    int deviceID;

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void sendCommand(DrawingCommand command);

private:
    Ui::MainWindow *ui;
    Canvas *canvas;
    ReceiveCanvas *receiveCanvas;
    QColor penColor;
    SendThread *sendThread;
    ReceivedThread *receivedThread;
    SafeQueue<QByteArray> commandQueue;


private slots:

    void commandFinished(DrawingCommand *command);

    void commandReceived(DrawingCommand command);
};

#endif // MAINWINDOW_H
