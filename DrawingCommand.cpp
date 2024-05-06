//
// Created by Administrator on 2024/4/29.
//

#include "DrawingCommand.h"


void DrawingCommand::setEnd(QPoint e) {
    this->end = e;
}

void DrawingCommand::setStart(QPoint s) {
    this->start = s;
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
    std::cout << " " << getDeviceID() << " " << getStart().x() << " " << getStart().y() << " " << getEnd().x() << " "
              << getEnd().y() << " " << getColor().red() << " " << getColor().green() << " " << getColor().blue() << " "
              << getWidth() << std::endl;
    std::cout << trace.size() << std::endl;
}

void DrawingCommand::setColor(QColor c) {
    this->color = std::move(c);
}

QColor DrawingCommand::getColor() const {
    return color;
}

void DrawingCommand::setWidth(int w) {
    this->width = w;
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
    auto commandType = static_cast<DrawingCommandType>(type);
    DrawingCommand command(commandType, deviceID, start, end, color, width, trace);
    return command;
}

int DrawingCommand::getDeviceID() const {
    return deviceID;
}

std::vector<int> DrawingCommand::toIntVector() const {
    std::vector<int> data;
    QByteArray serialized = serialize();
    data.reserve(serialized.size());
    for (int i = 0; i < serialized.size(); i++) {
        data.push_back((int) serialized.data()[i]);
    }
    return data;
}

std::vector<bool> DrawingCommand::toBoolVector() const {
    std::vector<bool> data;
    QByteArray serialized = serialize();
    data.reserve(serialized.size() * 8);
    for (int i = 0; i < serialized.size(); i++) {
        for (int j = 0; j < 8; j++) {
            data.push_back(serialized.data()[i] & (1 << j));
        }
    }
    return data;
}

std::vector<bool> DrawingCommand::qByteArrayToBoolVector(const QByteArray &data) {
    std::vector<bool> boolData;
    boolData.reserve(data.size() * 8);
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < 8; j++) {
            boolData.push_back(data.data()[i] & (1 << j));
        }
    }
    return boolData;
}
