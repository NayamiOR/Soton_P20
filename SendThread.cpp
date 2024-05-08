//
// Created by Administrator on 2024/5/2.
//

#include "SendThread.h"
#include <fstream>

[[noreturn]] void SendThread::run() {
    std::cout << "run send" << std::endl;
    Physical gpio(1,Pin::GPIO0, Pin::GPIO2, Pin::GPIO3,Pin::GPIO1);
    while (true) {
        if (!commandQueue.empty()) {
            auto data = commandQueue.front();
            std::vector<bool> bits = DrawingCommand::qByteArrayToBoolVector(data);
            std::cout<<"sending: "<<std::endl;
            for (auto i :bits){
                std::cout<<i;
            }
            std::cout<<std::endl<<std::endl;
            commandQueue.pop();

            gpio.setTransfering(true);
//            for (auto bit: bits) {
                for(int i=0;i<bits.size();i++){
                auto bit=bits[i];
                gpio.setData(bit);
                gpio.setSending(true);  //  发送
                if (i==bits.size()-1)
                    gpio.setTransfering(false);
                while (!gpio.getRead()) { ; }   //  等到被读过
                gpio.setSending(false); //  发送完了
                while (gpio.getRead()) { ;}     //  等到改成没读过
            }
            gpio.setTransfering(false);
        }
    }
}

void SendThread::sendSlot(DrawingCommand *command) {
    auto data = command->serialize();
    commandQueue.push(data);
}
