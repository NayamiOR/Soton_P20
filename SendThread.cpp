#include "SendThread.h"
#include <fstream>

[[noreturn]] void SendThread::run() {
    std::cout << "run send" << std::endl;
    while (true) {
        if (!commandQueue.empty()) {
            auto data = commandQueue.front();
            std::vector<bool> bits = DrawingCommand::qByteArrayToBoolVector(data);
            std::cout << "sending: " << std::endl;
            for (auto i: bits) {
                std::cout << i;
            }
            std::cout << std::endl << std::endl;
            commandQueue.pop();

            vars->transfering = true;
            for(int i = 0; i < bits.size(); i++) {
                bool bit = bits[i];
                vars->data = bit;
                vars->sending = true;
                if (i == bits.size() - 1) {
                    vars->transfering = false;
                }
                while (!vars->hasRead) { ; }
                vars->sending = false;
                while (vars->hasRead) { ; }
            }
            vars->transfering = false;
        }
    }
}

void SendThread::sendSlot(DrawingCommand *command) {
    auto data = command->serialize();
    commandQueue.push(data);
}
