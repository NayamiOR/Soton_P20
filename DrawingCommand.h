//
// Created by Administrator on 2024/4/29.
//

#ifndef P20_CODE_DRAWINGCOMMAND_H
#define P20_CODE_DRAWINGCOMMAND_H

#include <QPoint>
#include <utility>
#include <vector>
#include <iostream>
#include <QColor>
#include <QIODevice>
#include <QDataStream>

enum class DrawingCommandType {
    Line,
    Rect,
    Free,
    Ellipse,
    Clear
};

class DrawingCommand {
public:
    DrawingCommand(DrawingCommandType type, int id) : type(type), start(QPoint(0, 0)), end(QPoint(0, 0)),
                                                      color(Qt::black), deviceID(id),
                                                      width(2) {}

    DrawingCommand(DrawingCommandType type, int id, QPoint start) : type(type), start(start), end(QPoint(0, 0)),
                                                                    deviceID(id),
                                                                    color(Qt::black),
                                                                    width(2) {
        if (type == DrawingCommandType::Free)
            trace.push_back(start);
    }

    DrawingCommand(DrawingCommandType type, int id, QPoint start, QColor color, int width) : type(type), start(start),
                                                                                             deviceID(id),
                                                                                             end(QPoint(0, 0)),
                                                                                             color(std::move(color)),
                                                                                             width(width) {
        if (type == DrawingCommandType::Free)
            trace.push_back(start);
    }

    DrawingCommand(DrawingCommandType type, int id, QPoint start, QPoint end, QColor color, int width) : type(type),
                                                                                                         deviceID(id),
                                                                                                         start(start),
                                                                                                         end(end),
                                                                                                         color(std::move(
                                                                                                                 color)),
                                                                                                         width(width) {}

    DrawingCommand(DrawingCommandType type, int id, QPoint start, QPoint end, QColor color, int width,
                   std::vector<QPoint> trace) : type(type),
                                                deviceID(id),
                                                start(start),
                                                end(end),
                                                color(std::move(color)),
                                                width(width),
                                                trace(std::move(trace)) {}

    DrawingCommand(const QByteArray &data) {
        auto cmd = deserialize(data);
        this->type = cmd.getType();
        this->start = cmd.getStart();
        this->end = cmd.getEnd();
        this->color = cmd.getColor();
        this->width = cmd.getWidth();
        this->deviceID = cmd.getDeviceID();
        this->trace = cmd.getTrace();
    }

    DrawingCommand(const std::vector<int> &data) {
        QByteArray data2;
        for (int i: data) {
            data2.append((char) i);
        }
        auto cmd = deserialize(data2);
        this->type = cmd.getType();
        this->start = cmd.getStart();
        this->end = cmd.getEnd();
        this->color = cmd.getColor();
        this->width = cmd.getWidth();
        this->deviceID = cmd.getDeviceID();
        this->trace = cmd.getTrace();
    }

    DrawingCommand(const std::vector<bool> &data) {
        std::vector<int> data2;
        for (bool i: data) {
            data2.push_back(i);
        }
        QByteArray data3;
        for (int i: data2) {
            data3.append((char) i);
        }
        auto cmd = deserialize(data3);
        this->type = cmd.getType();
        this->start = cmd.getStart();
        this->end = cmd.getEnd();
        this->color = cmd.getColor();
        this->width = cmd.getWidth();
        this->deviceID = cmd.getDeviceID();
        this->trace = cmd.getTrace();
    }

    void setStart(QPoint s);

    QPoint getStart() const;

    void setEnd(QPoint e);

    QPoint getEnd() const;

    void addTrace(QPoint point);

    void setColor(QColor c);

    QColor getColor() const;

    void setWidth(int w);

    int getWidth() const;

    int getDeviceID() const;

    void printCommand() const;

    DrawingCommandType getType() const;

    std::vector<QPoint> getTrace() const;

    QByteArray serialize() const;

    static DrawingCommand deserialize(const QByteArray &data);

    std::vector<int> toIntVector() const;

    std::vector<bool> toBoolVector() const;

    static std::vector<bool> qByteArrayToBoolVector(const QByteArray &data);

private:
    DrawingCommandType type;
    int deviceID;
    QPoint start;
    QPoint end;
    QColor color;
    int width;
    std::vector<QPoint> trace;
};


#endif //P20_CODE_DRAWINGCOMMAND_H
