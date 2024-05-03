//
// Created by Administrator on 2024/5/2.
//

#include "SendThread.h"
#include <fstream>

SendThread::~SendThread() {
    if (currentCommand != nullptr) {
        delete currentCommand;
    }
}

void SendThread::run() {
    std::cout<<"run send"<<std::endl;
    while(true) {
        if (currentCommand != nullptr) {
//            currentCommand=new DrawingCommand(DrawingCommandType::Free,123);
            std::cout<<"receive command in sendthread"<<std::endl;
            currentCommand->printCommand();
            auto data = currentCommand->serialize();
            commandQueue.push(data);
            std::cout<<"send command"<<std::endl<<"----------------"<<std::endl;
            currentCommand = nullptr;
        }
    }
}

void SendThread::sendSlot(DrawingCommand *command) {
    currentCommand = command;
}

