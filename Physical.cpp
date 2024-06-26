#include "Physical.h"

void Physical::sendPin(Pin pin, bool bit) {
    pinMode((int)pin, OUTPUT);
    digitalWrite((int)pin, bit ? HIGH : LOW);
}

bool Physical::readPin(Pin pin) {
    return digitalRead((int) pin);
}

void Physical::setData(bool newData) {
    sendPin(data, newData);
}

bool Physical::getData() {
    return readPin(data);
}

void Physical::setSending(bool bit) {
    sendPin(sending, bit);
}

bool Physical::getSending() {
    return readPin(sending);
}

bool Physical::getRead() {
    return readPin(hasRead);
}

void Physical::setRead(bool bit) {
    sendPin(hasRead, bit);
}

void Physical::setTransfering(bool bit) {
    sendPin(transfering, bit);
}

bool Physical::getTransfering() {
    return readPin(transfering);
}

