#ifndef P20_CODE_RECEIVECANVAS_H
#define P20_CODE_RECEIVECANVAS_H


#define INIT_WIDTH 5000
#define INIT_HEIGHT 5000

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "DrawingCommand.h"

class ReceiveCanvas : public QWidget {
Q_OBJECT

public:
    ReceiveCanvas(QWidget *parent = nullptr,int deviceID=0);

protected:
    void paintEvent(QPaintEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void drawFreeCommand(DrawingCommand *command);

    void drawLineCommand(DrawingCommand *command);

    void drawRectCommand(DrawingCommand *command);

    void drawEllipseCommand(DrawingCommand *command);

    void clear();

private:
    QPoint lastPoint;
    QImage img;
    int deviceID;
public slots:

    void receiveCommand(DrawingCommand *command);
};


#endif //P20_CODE_RECEIVECANVAS_H
