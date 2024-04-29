//
// Created by Administrator on 2024/4/29.
//

#ifndef P20_CODE_RECEIVECANVAS_H
#define P20_CODE_RECEIVECANVAS_H



#define INIT_WIDTH 5000
#define INIT_HEIGHT 5000

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class ReceiveCanvas: public QWidget {
Q_OBJECT

public:
    ReceiveCanvas (QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QPoint lastPoint;
    QImage img;
};


#endif //P20_CODE_RECEIVECANVAS_H
