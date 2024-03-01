#include "inputs.h"

Canton::Canton(const CantonPins& cantonPins)
    : cantonPins(cantonPins) {}

void Canton::init() {
    Serial.println("Setting up " + String(cantonPins.name) + " on pin: " + String(cantonPins.pin) + "");

    pinMode(cantonPins.pin, INPUT);
}

bool Canton::readDigitalInput() const {
    return digitalRead(cantonPins.pin);
}

const char* Canton::getCantonName() const {
    return cantonPins.name;
}

bool* Canton::readAllDigitalInputs() const {
    bool* states = new bool[1];
    states[0] = digitalRead(cantonPins.pin);
    return states;
}
