#ifndef INPUTS_H
#define INPUTS_H

#include <Arduino.h>

class Canton {
public:
  // Structure pour représenter les broches des cantons
  struct CantonPins {
    uint8_t pin;
  };

  // Constructeur prenant la configuration des broches des cantons
  Canton(const CantonPins& cantonPins);

  void init();
  bool readDigitalInput(int pin);

private:
  // Déclaration des broches des cantons
  CantonPins cantonPins;
};

#endif