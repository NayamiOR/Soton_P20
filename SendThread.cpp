//
// Created by Administrator on 2024/5/2.
//

#include "SendThread.h"
#include <fstream>

[[noreturn]] void SendThread::run() {
    std::cout << "run send" << std::endl;
    while (true) {
        if (currentCommand != nullptr) {
            std::cout << "receive command in sendthread" << std::endl;
            currentCommand->printCommand();
            auto data = currentCommand->serialize();
            commandQueue.push(data);
            currentCommand = nullptr;
        }
    }
}

void SendThread::sendSlot(DrawingCommand *command) {
    currentCommand = command;
}

