//
// Created by Administrator on 2024/4/29.
//

#ifndef P20_CODE_DRAWINGCOMMAND_H
#define P20_CODE_DRAWINGCOMMAND_H

#include <QPoint>
#include<vector>
#include <iostream>
#include <QColor>

enum class DrawingCommandType {
    Line,
    Rect,
    Free,
    Ellipse,
    Clear
};

class DrawingCommand {
public:
    DrawingCommand(DrawingCommandType type) : type(type), start(QPoint(0, 0)), end(QPoint(0, 0)), color(Qt::black),
                                              width(2) {}

    DrawingCommand(DrawingCommandType type, QPoint start) : type(type), start(start), end(QPoint(0, 0)),
                                                            color(Qt::black),
                                                            width(2) {
        if (type == DrawingCommandType::Free)
            trace.push_back(start);
    }

    DrawingCommand(DrawingCommandType type, QPoint start, QPoint end, QColor color, int width) : type(type),
                                                                                                 start(start), end(end),
                                                                                                 color(color),
                                                                                                 width(width) {}

    void setStart(QPoint start);

    QPoint getStart() const;

    void setEnd(QPoint end);

    QPoint getEnd() const;

    void addTrace(QPoint point);

    void setColor(QColor color);

    QColor getColor() const;

    void setWidth(int width);

    int getWidth() const;

    void printCommand() const;

    DrawingCommandType getType() const;

    std::vector<QPoint> getTrace() const;

private:
    QPoint end;
    QPoint start;
    DrawingCommandType type;
    std::vector<QPoint> trace;
    QColor color;
    int width;
};


#endif //P20_CODE_DRAWINGCOMMAND_H
