#include "inputs.h"

const int Inputs::digitalPins[] = {34, 35, 32, 33, 25, 26, 27, 14, 17, 13, 4};
const int Inputs::numDigitalPins = sizeof(Inputs::digitalPins) / sizeof(Inputs::digitalPins[0]);

Inputs::Inputs() {
  // Constructor
}


void Inputs::setupInputs() {
  // Initialize input pins using a loop
  for (int i = 0; i < numDigitalPins; i++) {
    pinMode(digitalPins[i], INPUT);
  }
}




bool Inputs::readDigitalInput(int pin) {
  // Read and return digital input value
  return digitalRead(pin);
}

void Inputs::readDigitalAllInputs(bool* digitalPinValues) {
  // Read all digital inputs
  for (int i = 0; i < numDigitalPins; i++) {
    digitalPinValues[i] = digitalRead(digitalPins[i]);
  }
}
