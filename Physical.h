//
// Created by Administrator on 2024/5/3.
//

#ifndef P20_CODE_PHYSICAL_H
#define P20_CODE_PHYSICAL_H

//#include <wiringPi.h>

enum class Pin {
};

static const Pin InputPins[] = {
};

static const Pin OutputPins[] = {
};

class Physical {
public:
    Physical() {
        wiringPiSetup();
        for (auto pin : InputPins) {
            pinMode(static_cast<int>(pin), INPUT);
        }
        for (auto pin : OutputPins) {
            pinMode(static_cast<int>(pin), OUTPUT);
        }
    }

private:
    void send(int, bool);

    bool read(int);
};


#endif //P20_CODE_PHYSICAL_H
