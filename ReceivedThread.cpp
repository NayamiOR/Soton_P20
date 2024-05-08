//
// Created by Administrator on 2024/5/2.
//

#include "ReceivedThread.h"


[[noreturn]] void ReceivedThread::run() {
    std::cout << "run receive" << std::endl;
    Physical gpio(0, Pin::GPIO21, Pin::GPIO22, Pin::GPIO23, Pin::GPIO29);

    std::vector<bool> bits;
    while (true) {
        while (gpio.getSending()) { ; } //等到sending为false
        if (!gpio.getTransfering() && bits.size() != 0) {
            std::cout << "receiving: " << std::endl;
            for (auto i: bits) {
                std::cout << i;
            }
            std::cout << std::endl << std::endl;
            currentCommand = new DrawingCommand(bits);
            bits.clear();
            emit commandReceived(currentCommand);
        }
        gpio.setRead(false);    //  此时传完一位，sending循环结束一轮
//        delay(1);

        while (!gpio.getSending()) {    // when sending was set back to false and no new message is sending
            ;
        }
            bits.push_back(gpio.getData());
            gpio.setRead(true);     //读完之后设置read为true

    }
}
