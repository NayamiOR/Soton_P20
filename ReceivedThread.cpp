//
// Created by Administrator on 2024/5/2.
//

#include "ReceivedThread.h"


[[noreturn]] void ReceivedThread::run() {
    std::cout << "run receive" << std::endl;
    while (true) {
        if (commandQueue.empty()) {
            continue;
        }

        std::cout << "receive currentCommand in receivedthread" << std::endl;
        auto front = commandQueue.front();
        currentCommand = new DrawingCommand(front);
        std::cout << "Receive currentCommand: ";
        currentCommand->printCommand();
//        todo
//        if(currentCommand.getDeviceID()!=deviceID){
//            continue;
//        }
        commandQueue.pop();
        emit commandReceived(currentCommand);
    }
}

ReceivedThread::~ReceivedThread() {

}


