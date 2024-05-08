#ifndef P20_CODE_CANVAS_H
#define P20_CODE_CANVAS_H

#define INIT_WIDTH 5000
#define INIT_HEIGHT 5000

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "DrawingCommand.h"
#include <iostream>

class MainWindow;

class Canvas : public QWidget {
Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr,int id=0);

    DrawingCommandType penType;
    DrawingCommand *currentCommand;

    void setPenColor(QColor color);

    QColor getPenColor();

    void setPenWidth(int width);

    int getPenWidth();


protected:
    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QImage img;
    QImage tempImg;
    QImage lastImg;
    QPoint lastPoint;
    QColor penColor;
    int penWidth;
    int deviceID;

signals:

    void commandFinished(DrawingCommand *command);

public slots:

    void clear();
};


#endif //P20_CODE_CANVAS_H
