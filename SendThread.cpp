//
// Created by Administrator on 2024/5/2.
//

#include "SendThread.h"

SendThread::~SendThread() {

}

void SendThread::run() {
    if (currentCommand == nullptr) {
        return;
    }
    currentCommand->serialize();
    commandQueue.push(currentCommand->serialize());
    currentCommand = nullptr;
}

void SendThread::sendSlot(DrawingCommand *command) {
    currentCommand = command;
    run();
}

