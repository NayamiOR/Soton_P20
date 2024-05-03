//
// Created by Administrator on 2024/4/29.
//

#include "DrawingCommand.h"


void DrawingCommand::setEnd(QPoint end) {
    this->end = end;
}

void DrawingCommand::setStart(QPoint start) {
    this->start = start;
}

QPoint DrawingCommand::getStart() const {
    return start;
}

QPoint DrawingCommand::getEnd() const {
    return end;
}

DrawingCommandType DrawingCommand::getType() const {
    return type;
}

std::vector<QPoint> DrawingCommand::getTrace() const {
    return trace;
}

void DrawingCommand::addTrace(QPoint point) {
    trace.push_back(point);
}

void DrawingCommand::printCommand() const {
    switch (getType()) {
        case DrawingCommandType::Free:
            std::cout << "Free";
            break;
        case DrawingCommandType::Line:
            std::cout << "Line";
            break;
        case DrawingCommandType::Rect:
            std::cout << "Rect";
            break;
        case DrawingCommandType::Ellipse:
            std::cout << "Ellipse";
            break;
        case DrawingCommandType::Clear:
            std::cout << "Clear" << std::endl;
            return;
    }
}

void DrawingCommand::setColor(QColor color) {
    this->color = color;
}

QColor DrawingCommand::getColor() const {
    return color;
}

void DrawingCommand::setWidth(int width) {
    this->width = width;
}

int DrawingCommand::getWidth() const {
    return width;
}

QByteArray DrawingCommand::serialize() const {
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << start << end << static_cast<int>(type) << color << width << deviceID;
    if (type == DrawingCommandType::Free) {
        for (auto &point: trace) {
            stream << point;
        }
    }

    return data;
}

DrawingCommand DrawingCommand::deserialize(const QByteArray &data) {
    QDataStream stream(data);
    QPoint start, end;
    int type;
    QColor color;
    int width;
    int deviceID;
    std::vector<QPoint> trace;

    stream >> start >> end >> type >> color >> width >> deviceID;
    if (type == static_cast<int>(DrawingCommandType::Free)) {
        while (!stream.atEnd()) {
            QPoint point;
            stream >> point;
            trace.push_back(point);
        }
    }
    DrawingCommandType commandType = static_cast<DrawingCommandType>(type);
    DrawingCommand command(commandType, deviceID, start, end, color, width, trace);
    return command;
}

int DrawingCommand::getDeviceID() const {
    return deviceID;
}
