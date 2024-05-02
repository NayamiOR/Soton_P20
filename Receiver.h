//
// Created by Administrator on 2024/4/29.
//

#ifndef P20_CODE_RECEIVER_H
#define P20_CODE_RECEIVER_H

#include <QByteArray>
#include "DrawingCommand.h"

class Receiver {
public:
    void receiveData(const QByteArray &data);
};

// Receiver.cpp

#endif //P20_CODE_RECEIVER_H
