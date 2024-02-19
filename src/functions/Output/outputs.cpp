#include "outputs.h"

TrafficLight::TrafficLight(const GpioColors& gpioColors)
    : gpioColors_(gpioColors) {}


void TrafficLight::init() {
  // Configurez les broches GPIO comme sorties
  Serial.println("Setting up " + String(gpioColors_.name) + " on pins: " + String(gpioColors_.pins.pinR) + ", " + String(gpioColors_.pins.pinY) + ", " + String(gpioColors_.pins.pinG));

  gpioColors_.gpioR.pinMode(gpioColors_.pins.pinR, OUTPUT);
  gpioColors_.gpioY.pinMode(gpioColors_.pins.pinY, OUTPUT);
  gpioColors_.gpioG.pinMode(gpioColors_.pins.pinG, OUTPUT);

  // Éteignez toutes les LEDs au début
  gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, HIGH);
  gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, HIGH);
  gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, HIGH);
}

void TrafficLight::turnOnRed() {
  Serial.println("Turning on Red for " + String(gpioColors_.name) + "");
  gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, LOW);
  gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, HIGH);
  gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, HIGH);
}

void TrafficLight::turnOnYellow() {
  Serial.println("Turning on Yellow for " + String(gpioColors_.name) + "");
  gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, HIGH);
  gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, LOW);
  gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, HIGH);
}

void TrafficLight::turnOnGreen() {
  Serial.println("Turning on Green for " + String(gpioColors_.name) + "");
  gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, HIGH);
  gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, HIGH);
  gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, LOW);
}

void TrafficLight::turnOnAll() {
  Serial.println("Turning on all LEDs for " + String(gpioColors_.name) + "");
  gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, LOW);
  gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, LOW);
  gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, LOW);
}

void TrafficLight::turnOffAll() {
  Serial.println("Turning off all LEDs for " + String(gpioColors_.name) + "");
  gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, HIGH);
  gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, HIGH);
  gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, HIGH);
}