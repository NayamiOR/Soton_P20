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
        std::cout << "receive currentCommand: ";
        currentCommand->printCommand();
        std::cout << "----------------" << std::endl;

        for (auto &point: currentCommand->getTrace()) {
            std::cout << "receive: " << point.x() << " " << point.y() << std::endl;
        }
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


