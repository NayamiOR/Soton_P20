//
// Created by Administrator on 2024/4/29.
//

#ifndef P20_CODE_DRAWINGCOMMAND_H
#define P20_CODE_DRAWINGCOMMAND_H

#include <QPoint>
#include<vector>

enum class DrawingCommandType {
    Line,
    Rect,
    Free,
    Circle,
    Clear
};
class DrawingCommand {
public:
    DrawingCommand(DrawingCommandType type) : type(type) {}
    DrawingCommand(DrawingCommandType type, QPoint start, QPoint end) : type(type), start(start), end(end) {}
    void setStart(QPoint start) {
        this->start = start;
    }
    void setEnd(QPoint end) {
        this->end = end;
    }

private:
    QPoint end;
    QPoint start;
    DrawingCommandType type;
    std::vector<QPoint> trace;
};


#endif //P20_CODE_DRAWINGCOMMAND_H
