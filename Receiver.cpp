//
// Created by Administrator on 2024/4/29.
//

#include "Receiver.h"

void Receiver::receiveData(const QByteArray &data) {
    DrawingCommand command = DrawingCommand::deserialize(data);

}

