#ifndef INPUTS_H
#define INPUTS_H

#include <Arduino.h>
#include <vector>

class Canton {
public:
  struct CantonPins {
    uint8_t pin;
    const char* name;
  };

  Canton(const CantonPins& cantonPins);

  void init();
  bool readDigitalInput() const;
  const char* getCantonName() const;
  // Ajout de la nouvelle fonction
  bool* readAllDigitalInputs() const;

private:
  CantonPins cantonPins;
};

#endif