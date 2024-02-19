#include "outputs.h"

TrafficLight::TrafficLight(const GpioColors& gpioColors)
    : gpioColors_(gpioColors) {}



void TrafficLight::init() {
    // Configurez les broches GPIO comme sorties
    gpioColors_.gpioR.pinMode(gpioColors_.pins.pinR, OUTPUT);
    gpioColors_.gpioY.pinMode(gpioColors_.pins.pinY, OUTPUT);
    gpioColors_.gpioG.pinMode(gpioColors_.pins.pinG, OUTPUT);

    // Éteignez toutes les LEDs au début
    gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, HIGH);
    gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, HIGH);
    gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, HIGH);
}

void TrafficLight::turnOnRed() {
    gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, LOW);
    gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, HIGH);
    gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, HIGH);
}

void TrafficLight::turnOnYellow() {
    gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, HIGH);
    gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, LOW);
    gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, HIGH);
  }

void TrafficLight::turnOnGreen() {
    gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, HIGH);
    gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, HIGH);
    gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, LOW);
  }

void TrafficLight::turnOnAll() {
    gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, LOW);
    gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, LOW);
    gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, LOW);
  }

void TrafficLight::turnOffAll() {
    gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, HIGH);
    gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, HIGH);
    gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, HIGH);
  }









// Outputs::Outputs() {
//   // Constructor
// }

// void Outputs::setupOutputs() {
//   // Initialize output pins using a loop
//   gpio1.begin(PCAL9535A::HardwareAddress::A000);  // 0x20 - Pins = 000  => Puce N°1
//   gpio2.begin(PCAL9535A::HardwareAddress::A001);  // 0x21 - Pins = 001  => Puce N°2
//   gpio3.begin(PCAL9535A::HardwareAddress::A010);  // 0x22 - Pins = 010  => Puce N°3
//   gpio4.begin(PCAL9535A::HardwareAddress::A011);  // 0x23 - Pins = 011  => Puce N°4

// }














// /////////////////////////////////////////////////////////////////
// void turnAllOutputsOn(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio) {
//   for (int i = 0; i < 16; ++i) {
//     // Invert the logic for pins 0-7 on gpio3 and pins 0-15 on gpio4
//     if ((&gpio == &gpio3 && i < 8) || (&gpio == &gpio4 && i < 16)) {
//       gpio.digitalWrite(i, HIGH);
//     } else {
//       gpio.digitalWrite(i, LOW);
//     }
//   }
// }


// void turnAllOutputsOff(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio) {
//   for (int i = 0; i < 16; ++i) {
//     // Invert the logic for pins 0-7 on gpio3 and pins 0-15 on gpio4
//     if ((&gpio == &gpio3 && i < 8) || (&gpio == &gpio4 && i < 16)) {
//       gpio.digitalWrite(i, LOW);
//     } else {
//       gpio.digitalWrite(i, HIGH);
//     }
//   }
// }


// void invertAllOutputs(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio) {
//   for (int i = 0; i < 16; ++i) {
//     uint8_t currentValue = gpio.digitalRead(i);
//     gpio.digitalWrite(i, !currentValue);
//   }
// }


// void setOutputsStates(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio, uint16_t ledStates) {
//   for (int i = 0; i < 16; ++i) {
//     bool isLedOn = (ledStates & (1 << i)) != 0;
//     gpio.digitalWrite(i, isLedOn ? HIGH : LOW);
//   }
// }





// //A voir
// uint16_t getAllPortStates(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio) {
//   uint16_t portStates = 0;
//   for (int i = 0; i < 16; ++i) {
//     portStates |= (gpio.digitalRead(i) << i);
//   }
//   return portStates;
// }

// uint8_t getPortState(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio, PCAL9535A::Port port) {
//   uint8_t portState = 0;
//   for (int i = 0; i < 8; ++i) {
//     portState |= (gpio.digitalRead(static_cast<int>(port) * 8 + i) << i);
//   }
//   return portState;
// }