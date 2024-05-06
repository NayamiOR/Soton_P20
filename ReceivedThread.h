//
// Created by Administrator on 2024/5/2.
//

#ifndef P20_CODE_RECEIVEDTHREAD_H
#define P20_CODE_RECEIVEDTHREAD_H

#include <vector>
#include <QThread>

#include "ReceiveCanvas.h"
#include "DrawingCommand.h"
#include "SafeQueue.h"
#include "Physical.h"

class ReceivedThread : public QThread {
Q_OBJECT
public:
    ReceivedThread(int id, SafeQueue<QByteArray> &queue, ReceiveCanvas *canvas) : deviceID(id), commandQueue(queue),
                                                                                  canvas(canvas), currentCommand(
                    nullptr) {};

    [[noreturn]] void run() override;
    DrawingCommand getCommand();


signals:
    void commandReceived(DrawingCommand *command);

private:
    SafeQueue<QByteArray> &commandQueue;
    int deviceID;
    DrawingCommand *currentCommand;
    ReceiveCanvas *canvas;
};


#endif //P20_CODE_RECEIVEDTHREAD_H
