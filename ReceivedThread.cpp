//
// Created by Administrator on 2024/5/2.
//

#include "ReceivedThread.h"

void ReceivedThread::receiveSlot(QByteArray message) {

}

void ReceivedThread::run(){
    QThread::run();
}

ReceivedThread::~ReceivedThread() {
}
