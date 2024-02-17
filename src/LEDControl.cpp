// LEDControl.cpp
#include "./functions/LEDControl.h"

void turnAllLedsOn(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio) {
  for (int i = 0; i < 16; ++i) {
    // Invert the logic for pins 0-7 on gpio3 and pins 0-15 on gpio4
    if ((&gpio == &gpio3 && i < 8) || (&gpio == &gpio4 && i < 16)) {
      gpio.digitalWrite(i, HIGH);
    } else {
      gpio.digitalWrite(i, LOW);
    }
  }
}


void turnAllLedsOff(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio) {
  for (int i = 0; i < 16; ++i) {
    // Invert the logic for pins 0-7 on gpio3 and pins 0-15 on gpio4
    if ((&gpio == &gpio3 && i < 8) || (&gpio == &gpio4 && i < 16)) {
      gpio.digitalWrite(i, LOW);
    } else {
      gpio.digitalWrite(i, HIGH);
    }
  }
}


void invertAllPins(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio) {
  for (int i = 0; i < 16; ++i) {
    uint8_t currentValue = gpio.digitalRead(i);
    gpio.digitalWrite(i, !currentValue);
  }
}


void setLedStates(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio, uint16_t ledStates) {
  for (int i = 0; i < 16; ++i) {
    bool isLedOn = (ledStates & (1 << i)) != 0;
    gpio.digitalWrite(i, isLedOn ? HIGH : LOW);
  }
}


uint16_t getAllPortStates(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio) {
  uint16_t portStates = 0;
  for (int i = 0; i < 16; ++i) {
    portStates |= (gpio.digitalRead(i) << i);
  }
  return portStates;
}

uint8_t getPortState(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio, PCAL9535A::Port port) {
  uint8_t portState = 0;
  for (int i = 0; i < 8; ++i) {
    portState |= (gpio.digitalRead(static_cast<int>(port) * 8 + i) << i);
  }
  return portState;
}