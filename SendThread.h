//
// Created by Administrator on 2024/5/2.
//

#ifndef P20_CODE_SENDTHREAD_H
#define P20_CODE_SENDTHREAD_H

#include <QThread>
#include "SafeQueue.h"
#include "DrawingCommand.h"
#include "SharedVariables.h"

class SendThread : public QThread {
Q_OBJECT
public:
    SendThread(int id, SafeQueue<QByteArray> &queue)
            : deviceID(id), commandQueue(queue), currentCommand(nullptr) {
        std::cout << "SendThread created" << std::endl;
    }
    SendThread(int id, SafeQueue<QByteArray> &queue, SharedVariables *vars)
            : deviceID(id), commandQueue(queue), currentCommand(nullptr), vars(vars){
        std::cout << "SendThread created" << std::endl;
    }

    [[noreturn]] void run() override;

public slots:

    void sendSlot(DrawingCommand *command);

private:
    SharedVariables *vars;
    SafeQueue<QByteArray> &commandQueue;
    int deviceID;
    DrawingCommand *currentCommand;
};


#endif //P20_CODE_SENDTHREAD_H
