//
// Created by Administrator on 2024/4/25.
//

#include "canvas.h"

Canvas::Canvas(QWidget *parent) {
    img = QImage(INIT_WIDTH, INIT_HEIGHT, QImage::Format_RGB32);
    img.fill(Qt::white);
    tempImg = QImage(INIT_WIDTH, INIT_HEIGHT, QImage::Format_RGB32);
//    tempImg.fill(Qt::transparent);
    tempImg.fill(Qt::white);
//    set lastImg a copy of Img
    lastImg = img;
    penColor = Qt::black;
    penType = DrawingCommandType::Free;
    currentCommand = nullptr;
}

// MOUSE EVENTS SECTION STARTS HERE

// runs once when the mouse is pressed
void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        lastImg = img;
    }
    if (currentCommand == nullptr) {
        currentCommand = new DrawingCommand(penType, lastPoint);
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        // draw the trace (preview) of the line
        QPainter painter(&tempImg);
        painter.setPen(QPen(penColor, 2));
        switch (penType) {
            case DrawingCommandType::Free:
                painter.drawLine(lastPoint, event->pos());
                lastPoint = event->pos();
                break;
            case DrawingCommandType::Line:
//                empty last preview
                painter.drawImage(0, 0, lastImg);
//                draw new preview
                painter.drawLine(lastPoint, event->pos());
                break;
            case DrawingCommandType::Rect:
                painter.drawImage(0, 0, lastImg);
                painter.drawRect(QRect(lastPoint, event->pos()));
                break;
            case DrawingCommandType::Ellipse:
                painter.drawImage(0, 0, lastImg);
                painter.drawEllipse(QRect(lastPoint, event->pos()));
                break;
        }

        update();
        emit imgChanged();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (currentCommand == nullptr) {
        return;
    }
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        //完成当前命令，TODO: 把当前命令加入到命令列表中
        currentCommand->setEnd(event->pos());
        //把tempImg画到img上
        QPainter painter(&img);
        painter.drawImage(QPoint(0, 0), tempImg);
        //清空tempImg
//        tempImg.fill(Qt::transparent);
        QPainter painter2(&tempImg);
        painter2.drawImage(QPoint(0, 0), img);
        update();
        emit imgChanged();
    }
}

// MOUSE EVENTS SECTION ENDS HERE

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect rect = event->rect();
    painter.drawImage(rect, img, rect);
    painter.drawImage(rect, tempImg, rect);
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
    tempImg.fill(Qt::white);
    lastImg=img;
    update();
    emit imgChanged();
}
