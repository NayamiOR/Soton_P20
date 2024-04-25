//
// Created by Administrator on 2024/4/25.
//

#include "canvas.h"

Canvas::Canvas(QWidget *parent) {
    img = QImage(size(), QImage::Format_RGB32);
    img.fill(Qt::white);
    painter = new QPainter(&img);
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        if (img.isNull()) {
            img = QImage(size(), QImage::Format_RGB32);
            img.fill(Qt::white);
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
//        QPainter painter(&img);
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }
}

void Canvas::paintEvent(QPaintEvent *event) {
//    QPainter painter(this);
    painter.drawImage(rect(), img);
}

void Canvas::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    if (!img.isNull()) {
        QImage newImg(size(), QImage::Format_RGB32);
        newImg.fill(Qt::white);
//        QPainter painter(&newImg);
        painter.drawImage(QPoint(), img);
        img = newImg;
    }
}
