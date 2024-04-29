//
// Created by Administrator on 2024/4/25.
//

#include "ReceiveCanvas.h"

ReceiveCanvas::ReceiveCanvas(QWidget *parent) {
    img = QImage(INIT_WIDTH, INIT_HEIGHT, QImage::Format_RGB32);
    img.fill(Qt::white);
}


void ReceiveCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect rect = event->rect();
    painter.drawImage(rect, img, rect);
}

void ReceiveCanvas::resizeEvent(QResizeEvent *event) {
    if (!img.isNull()) {
        QPainter painter(&img);
        painter.drawImage(QPoint(0, 0), img);
    } else {
        img = QImage(INIT_WIDTH, INIT_HEIGHT, QImage::Format_RGB32);
        img.fill(Qt::white);
    }
}