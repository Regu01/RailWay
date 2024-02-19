#include "inputs.h"

Canton::Canton(const CantonPins& cantonPins)
    : cantonPins(cantonPins) {}

void Canton::init() {
    // Configurez les broches GPIO comme sorties
    Serial.print("Setting up Canton on pin : ");
    Serial.println(cantonPins.pin);

    pinMode(cantonPins.pin, INPUT);
}

bool Canton::readDigitalInput(int pin) {
  return digitalRead(pin);
}
