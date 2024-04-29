//
// Created by Administrator on 2024/4/29.
//

#ifndef P20_CODE_SENDER_H
#define P20_CODE_SENDER_H

#include "DrawingCommand.h"
#include <wiringPi.h>


class Sender {
public:
    void sendCommand(DrawingCommand command);
};


#endif //P20_CODE_SENDER_H
