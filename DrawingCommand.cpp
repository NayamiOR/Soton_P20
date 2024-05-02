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
    std::cout << "Complete Command: ";
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
    std::cout << " where starts at (" << getStart().x() << "," << getStart().y() << ") and ends at (" << getEnd().x()
              << "," << getEnd().y() << ")" << std::endl;

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
    return data;
}

DrawingCommand DrawingCommand::deserialize(const QByteArray &data) {
    QDataStream stream(data);
    QPoint start, end;
    int type;
    QColor color;
    int width;
    int deviceID;
    stream >> start >> end >> type >> color >> width >> deviceID;
    DrawingCommandType commandType = static_cast<DrawingCommandType>(type);
    DrawingCommand command(commandType, deviceID, start, end, color, width);
}

int DrawingCommand::getDeviceID() const {
    return deviceID;
}
