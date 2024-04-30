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