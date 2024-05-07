//
// Created by Administrator on 2024/5/2.
//

#include "ReceivedThread.h"


[[noreturn]] void ReceivedThread::run() {
    std::cout << "run receive" << std::endl;
    Physical gpio(0,Pin::GPIO21, Pin::GPIO22, Pin::GPIO23,Pin::GPIO29);
//    TODO：重构这里
/*
while(1){
        // When remote stops sending, make read
        // confirmation flag LOW
        while(readPin(data->serial_pins->isSending))
            ;
        writePin(data->serial_pins->hasRead, FALSE);
        while(!readPin(data->serial_pins->isSending))
            ;
        bits.push_back(readPin(data->serial_pins->data));
        // If the message has the right size
        if(bits.size() == SerialSender::messageSize() ){
            // Tells Viewer to draw the point, serialised as bits.
            data->receiver->decoder(bits);
            bits.clear();
        }
        writePin(data->serial_pins->hasRead, TRUE);
    }
*/
    std::vector<bool> bits;
    while (true) {
        while (gpio.getSending()) { ; } //等到sending为false
        gpio.setRead(false);    //  此时传完一位，sending循环结束一轮
//        std::cout<<"sending is false and set read to false"<<std::endl;
        delay(1);
        if (!gpio.getTransfering()&&bits.size()!=0) {
            std::cout<<"receiving: "<<std::endl;
            for (auto i :bits){
                std::cout<<i<<" ";
            }
            std::cout<<std::endl<<std::endl;
            currentCommand=new DrawingCommand(bits);
            bits.clear();
            emit commandReceived(currentCommand);
        }
        while (!gpio.getSending()) {    // when sending was set back to false and no new message is sending
            ;
            // 本作用域中sending恒为false
//            if (!gpio.getTransfering()) {
//                std::cout<<"receiving: "<<std::endl;
//                for (auto i :bits){
//                    std::cout<<i<<" ";
//                }
//                std::cout<<std::endl<<std::endl;
//                currentCommand=new DrawingCommand(bits);
//                bits.clear();
//                emit commandReceived(currentCommand);
//            }
         }    //等到sending为true
        bits.push_back(gpio.getData());
        gpio.setRead(true);     //读完之后设置read为true
//        std::cout<<"now sending is true and set read to true"<<std::endl;

//        if (commandQueue.empty()) {
//            continue;
//        }
//        std::cout << "receive currentCommand in receivedthread" << std::endl;
//        auto front = commandQueue.front();
//        currentCommand = new DrawingCommand(front);
//        std::cout << "Receive currentCommand: ";
//        currentCommand->printCommand();
//        commandQueue.pop();
//        emit commandReceived(currentCommand);
    }
}

DrawingCommand ReceivedThread::getCommand() {
    auto front = commandQueue.front();
    DrawingCommand command(front);
    commandQueue.pop();
    return command;
}
