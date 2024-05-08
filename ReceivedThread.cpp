#include "ReceivedThread.h"


[[noreturn]] void ReceivedThread::run() {
    std::cout << "run receive" << std::endl;
    std::vector<bool> bits;
    while (true) {
        while (vars->sending) { ; }
        if (!vars->transfering && bits.size() != 0) {
            for (auto i: bits) {
                std::cout << i;
            }
            currentCommand = new DrawingCommand(bits);
            bits.clear();
            emit commandReceived(currentCommand);
        }
        vars->hasRead = false;
        while (!vars->sending) { ; }
        bits.push_back(vars->data);
        vars->hasRead = true;
    }
}
