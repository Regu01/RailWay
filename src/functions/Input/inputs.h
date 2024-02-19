#ifndef INPUTS_H
#define INPUTS_H

#include <Arduino.h>

class Inputs {
public:
  Inputs();
  void setupInputs();
  bool readDigitalInput(int pin);
  void readDigitalAllInputs(bool* digitalPinValue);


private:
  static const int digitalPins[];
  static const int numDigitalPins;

};

#endif
