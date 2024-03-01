#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <Arduino.h>
#include <AceWire.h>
#include "../PCAL9535A.h"

using ace_wire::SimpleWireInterface;
extern PCAL9535A::PCAL9535A<SimpleWireInterface> gpio1;
extern PCAL9535A::PCAL9535A<SimpleWireInterface> gpio2;
extern PCAL9535A::PCAL9535A<SimpleWireInterface> gpio3;
extern PCAL9535A::PCAL9535A<SimpleWireInterface> gpio4;


class TrafficLight {
public:
  // Structure pour représenter les broches et couleurs d'un feu
  struct LightPins {
    uint8_t pinR;
    uint8_t pinY;
    uint8_t pinG;
  };

  // Structure pour représenter les GPIO associées à chaque couleur
  struct GpioColors {
    PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpioR;
    PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpioY;
    PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpioG;
    LightPins pins;
    const char* name;
  };

  // Constructeur
  TrafficLight(const GpioColors &gpioColors);

  void init();
  void turnOnRed();
  void turnOnYellow();
  void turnOnGreen();
  void turnOnAll();
  void turnOffAll();
  

private:
  // Référence vers la structure GPIO associée à chaque couleur
  const GpioColors& gpioColors_;
  const char *name_;
};




#endif
