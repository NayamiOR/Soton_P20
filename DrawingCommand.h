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
    Ellipse,
    Clear
};

class DrawingCommand {
public:
    DrawingCommand(DrawingCommandType type) : type(type) {}

    DrawingCommand(DrawingCommandType type, QPoint start) : type(type), start(start) {
        if (type == DrawingCommandType::Free)
            trace.push_back(start);
    }

    DrawingCommand(DrawingCommandType type, QPoint start, QPoint end) : type(type), start(start), end(end) {}

    void setEnd(QPoint end) ;
    void setStart(QPoint start) ;
    QPoint getStart() const;
    QPoint getEnd() const;
    DrawingCommandType getType() const;

private:
    QPoint end;
    QPoint start;
    DrawingCommandType type;
    std::vector<QPoint> trace;
};


#endif //P20_CODE_DRAWINGCOMMAND_H
