#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include "canvas.h"

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
    QColor penColor;

private slots:
    void setBlack();
    void setRed();
    void setGreen();
    void setBlue();
    void setYellow();
    void setWhite();
    void setCyan();
    void setMagenta();
    void setClear();
    void setEraser();
};

#endif // MAINWINDOW_H
