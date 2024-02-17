#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <AceWire.h>
#include "PCAL9535A.h"

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
  };

  // Constructeur
  TrafficLight(const GpioColors& gpioColors)
      : gpioColors_(gpioColors) {}

  // Initialisation du feu de signalisation
  void init() {
    // Configurez les broches GPIO comme sorties
    gpioColors_.gpioR.pinMode(gpioColors_.pins.pinR, OUTPUT);
    gpioColors_.gpioY.pinMode(gpioColors_.pins.pinY, OUTPUT);
    gpioColors_.gpioG.pinMode(gpioColors_.pins.pinG, OUTPUT);

    // Éteignez toutes les LEDs au début
    gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, HIGH);
    gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, HIGH);
    gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, HIGH);
  }

  // Fonction pour allumer la LED rouge
  void turnOnRed() {
    gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, LOW);
    gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, HIGH);
    gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, HIGH);
  }

  // Fonction pour allumer la LED jaune
  void turnOnYellow() {
    gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, HIGH);
    gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, LOW);
    gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, HIGH);
  }

  // Fonction pour allumer la LED verte
  void turnOnGreen() {
    gpioColors_.gpioR.digitalWrite(gpioColors_.pins.pinR, HIGH);
    gpioColors_.gpioY.digitalWrite(gpioColors_.pins.pinY, HIGH);
    gpioColors_.gpioG.digitalWrite(gpioColors_.pins.pinG, LOW);
  }

private:
  // Référence vers la structure GPIO associée à chaque couleur
  const GpioColors& gpioColors_;
};

#endif // TRAFFICLIGHT_H
