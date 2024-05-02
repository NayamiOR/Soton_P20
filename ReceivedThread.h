//
// Created by Administrator on 2024/5/2.
//

#ifndef P20_CODE_RECEIVEDTHREAD_H
#define P20_CODE_RECEIVEDTHREAD_H

#include <QThread>
#include "SafeQueue.h"

class ReceivedThread : public QThread {
Q_OBJECT
public:
    ReceivedThread(int id, SafeQueue<QByteArray> &queue) : deviceID(id), commandQueue(queue) {}

    ~ReceivedThread();

    void run() override;

public slots:

    void receiveSlot(QByteArray message);

private:
    SafeQueue<QByteArray> &commandQueue;
    int deviceID;
};


#endif //P20_CODE_RECEIVEDTHREAD_H
