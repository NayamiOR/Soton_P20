//
// Created by Administrator on 2024/5/2.
//

#include "SendThread.h"
#include <fstream>

[[noreturn]] void SendThread::run() {
    std::cout << "run send" << std::endl;
    //  TODO: 暂时把GPIO接口创建放在这里
    Physical gpio(1,Pin::GPIO0, Pin::GPIO2, Pin::GPIO3,Pin::GPIO1);
    //  TODO: GPIO线程写在这里
    while (true) {
        if (!commandQueue.empty()) {
            auto data = commandQueue.front();
            std::vector<bool> bits = DrawingCommand::qByteArrayToBoolVector(data);
            commandQueue.pop();
            /*
            for(unsigned int i = 0; i<bitfield.size(); i++){
                writePin(data->serial_pins->data, bitfield[i]);
                writePin(data->serial_pins->isSending, TRUE);
                while(!readPin(data->serial_pins->hasRead)) //被读过
                    ;
                writePin(data->serial_pins->isSending, FALSE);//读完就算发送完了
                while(readPin(data->serial_pins->hasRead))  //等到改成没被读过
                    ;
            }
            */
            gpio.setTransfering(true);
            for (auto bit: bits) {
                gpio.setData(bit);
                gpio.setSending(true);  //  发送
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
