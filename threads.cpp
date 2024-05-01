//
// Created by Administrator on 2024/5/1.
//

#include "threads.h"

threads::threads(int id) {
    deviceID = id;
    // TODO: create threads
    senderThread = new std::thread([this]() {
        Sender sender;
        for(;;) {

        }
    });

    // TODO
    receiverThread = new std::thread([this]() {
        Receiver receiver;
        for(;;) {
            if (!commandQueue.empty()) {
                DrawingCommand command = DrawingCommand::deserialize(commandQueue.front());
                if (command.getDeviceID() != deviceID) {
                    continue;
                }
                commandQueue.pop();
                Sender::sendCommand(command);
            }
        }
    });
}

threads::~threads() {
    delete senderThread;
    delete receiverThread;
}