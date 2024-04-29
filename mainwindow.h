#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "canvas.h"
#include "ReceiveCanvas.h"
#include <vector>
#include <unordered_map>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include "colors.h"
#include <QHBoxLayout>
#include "DrawingCommand.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Canvas *canvas;
    ReceiveCanvas *receiveCanvas;
    QColor penColor;

private slots:

};

#endif // MAINWINDOW_H
