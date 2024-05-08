#ifndef P20_CODE_PHYSICAL_H
#define P20_CODE_PHYSICAL_H

#include <wiringPi.h>
#include <condition_variable>
#include <mutex>

enum class Pin {
    /*
    PinName = WiringPiPin // PhysicalPin
    */

    GPIO0 = 0,  // 11
    GPIO1 = 1,  // 12
    GPIO2 = 2,  // 13
    GPIO3 = 3,  // 15
    GPIO4 = 4,  // 16
    GPIO5 = 5,  // 18
    GPIO6 = 6,  // 22
    GPIO7 = 7,  // 7
    GPIO21 = 21,  // 29
    GPIO22 = 22,  // 31
    GPIO23 = 23,  // 33
    GPIO24 = 24,  // 35
    GPIO25 = 25,  // 37
    GPIO26 = 26,  // 32
    GPIO27 = 27,  // 36
    GPIO28 = 28,  // 38
    GPIO29 = 29,  // 40
    TxD = 15,  // 8
    RxD = 16,  // 10
};

class Physical {
public:
    Physical(int mode, Pin data, Pin isReady, Pin hasRead, Pin transfering) : data(data), sending(isReady),
                                                                              hasRead(hasRead),
                                                                              transfering(transfering) {
        if (mode == 1) {                //发送端
            pinMode(static_cast<int>(data), OUTPUT);
            pinMode(static_cast<int>(isReady), OUTPUT);
            pinMode(static_cast<int>(hasRead), INPUT);
            pinMode(static_cast<int>(transfering), OUTPUT);
            digitalWrite((int)isReady,LOW);
            digitalWrite((int)transfering,LOW);
        } else if (mode == 0) {         //接收端
            pinMode(static_cast<int>(data), INPUT);
            pinMode(static_cast<int>(isReady), INPUT);
            pinMode(static_cast<int>(hasRead), OUTPUT);
            pinMode(static_cast<int>(transfering), INPUT);
            digitalWrite((int)hasRead,LOW);
        }
    }

    void sendPin(Pin, bool);

    bool readPin(Pin);

    void setData(bool);

    bool getData();

    void setSending(bool);

    bool getSending();

    bool getRead();

    void setRead(bool);

    void setTransfering(bool);

    bool getTransfering();

private:
    Pin data;
    Pin sending;
    Pin hasRead;
    Pin transfering;
};


#endif //P20_CODE_PHYSICAL_H
