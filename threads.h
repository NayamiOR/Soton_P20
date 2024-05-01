//
// Created by Administrator on 2024/5/1.
//

#ifndef P20_CODE_THREADS_H
#define P20_CODE_THREADS_H

#include <thread>
#include "Sender.h"
#include "SafeQueue.h"
#include "Receiver.h"
#include "DrawingCommand.h"

class threads {
public:
    threads(int id);

    ~threads();
    int getDeviceID() const {
        return deviceID;
    }


private:
    std::thread *receiverThread;
    std::thread *senderThread;
    SafeQueue<QByteArray> commandQueue;
    int deviceID;
};


#endif //P20_CODE_THREADS_H
