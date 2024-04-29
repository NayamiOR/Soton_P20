//
// Created by Administrator on 2024/4/25.
//

#include "canvas.h"

Canvas::Canvas(QWidget *parent) {
    img = QImage(INIT_WIDTH, INIT_HEIGHT, QImage::Format_RGB32);
    img.fill(Qt::white);
    penColor = Qt::black;
    penType = DrawingCommandType::Free;
    currentCommand = nullptr;
}

// MOUSE EVENTS SECTION STARTS HERE

// runs once when the mouse is pressed
void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
//        QPainter painter(&img);
//        painter.setPen(QPen(penColor, 2));
//        painter.drawLine(lastPoint, event->pos());
//        lastPoint = event->pos();

        update();
        emit imgChanged();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (currentCommand == nullptr) {
        return;
    }
    if (event->button() == Qt::LeftButton) {
        currentCommand->setEnd(event->pos());
        sendCommand(currentCommand);
        update();
        emit imgChanged();
    }
}

// MOUSE EVENTS SECTION ENDS HERE

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect rect = event->rect();
    painter.drawImage(rect, img, rect);
}

void Canvas::resizeEvent(QResizeEvent *event) {
    if (!img.isNull()) {
        QPainter painter(&img);
        painter.drawImage(QPoint(0, 0), img);
    } else {
        img = QImage(INIT_WIDTH, INIT_HEIGHT, QImage::Format_RGB32);
        img.fill(Qt::white);
    }
}

void Canvas::clear() {
    img.fill(Qt::white);
    update();
    emit imgChanged();
}
