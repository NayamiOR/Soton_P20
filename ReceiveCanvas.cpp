//
// Created by Administrator on 2024/4/25.
//

#include "ReceiveCanvas.h"
#include "canvas.h"

ReceiveCanvas::ReceiveCanvas(QWidget *parent) {
    img = QImage(INIT_WIDTH, INIT_HEIGHT, QImage::Format_RGB32);
    img.fill(Qt::white);
    Canvas parentCanvas;
    connect(&parentCanvas, &Canvas::commandFinished, this, &ReceiveCanvas::receiveCommand);
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

void ReceiveCanvas::drawFreeCommand(DrawingCommand *command) {
    QPainter painter(&img);
    painter.setPen(QPen(command->getColor(), command->getWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    if (command->getTrace().size() < 2) {
        return;
    }
    for (int i = 1; i < command->getTrace().size(); i++) {
        QPoint p1 = command->getTrace().at(i - 1);
        QPoint p2 = command->getTrace().at(i);
        painter.drawLine(p1, p2);
    }
}

void ReceiveCanvas::drawLineCommand(DrawingCommand *command) {
    QPainter painter(&img);
    painter.setPen(QPen(command->getColor(), command->getWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(command->getStart(), command->getEnd());
}

void ReceiveCanvas::drawRectCommand(DrawingCommand *command) {
    QPainter painter(&img);
    painter.setPen(QPen(command->getColor(), command->getWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawRect(QRect(command->getStart(), command->getEnd()));
}

void ReceiveCanvas::drawEllipseCommand(DrawingCommand *command) {
    QPainter painter(&img);
    painter.setPen(QPen(command->getColor(), command->getWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawEllipse(QRect(command->getStart(), command->getEnd()));
}

void ReceiveCanvas::clear() {
    img.fill(Qt::white);
    update();
}

void ReceiveCanvas::receiveCommand(DrawingCommand *command) {
    command->printCommand();
    switch (command->getType()) {
        case DrawingCommandType::Free:
            drawFreeCommand(command);
            break;
        case DrawingCommandType::Line:
            drawLineCommand(command);
            break;
        case DrawingCommandType::Rect:
            drawRectCommand(command);
            break;
        case DrawingCommandType::Ellipse:
            drawEllipseCommand(command);
            break;
        case DrawingCommandType::Clear:
            clear();
            break;
    }
    update();
}