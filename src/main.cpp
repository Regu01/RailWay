#include <Arduino.h>
#include <AceWire.h>
#include "./functions/PCAL9535A.h"
#include "./functions/TrafficLight.h"


///////////////////////////////////////
///// GESTION RETROSIGNIALISATION /////
///////////////////////////////////////

using ace_wire::SimpleWireInterface;

constexpr int PIN_SDA = 21;
constexpr int PIN_SCL = 22;
constexpr uint8_t DELAY_MICROS = 1;

// Create the AceWire SimpleWireInterface
SimpleWireInterface wire(PIN_SDA, PIN_SCL, DELAY_MICROS);

// Create PCAL9535A instance with reference to SimpleWireInterface
PCAL9535A::PCAL9535A<SimpleWireInterface> gpio1(wire);
PCAL9535A::PCAL9535A<SimpleWireInterface> gpio2(wire);
PCAL9535A::PCAL9535A<SimpleWireInterface> gpio3(wire);
PCAL9535A::PCAL9535A<SimpleWireInterface> gpio4(wire);

// Configuration des broches pour chaque couleur et GPIO associées
const TrafficLight::GpioColors trafficLight1Pins{
    gpio1, // GPIO pour la couleur rouge
    gpio1, // GPIO pour la couleur jaune
    gpio1, // GPIO pour la couleur verte
    {6, 7, 2} // Broches pour chaque couleur (Rouge, Jaune, Vert)
};

const TrafficLight::GpioColors trafficLight11Pins{
    gpio2, // GPIO pour la couleur rouge
    gpio2, // GPIO pour la couleur jaune
    gpio3, // GPIO pour la couleur verte
    {1, 0, 12} // Broches pour chaque couleur (Rouge, Jaune, Vert)
};

// Créez les instances TrafficLight correspondantes
TrafficLight trafficLight1(trafficLight1Pins);
TrafficLight trafficLight11(trafficLight11Pins);
// TrafficLight trafficLight1(trafficLight1Pins);
// TrafficLight trafficLight2(trafficLight2Pins);
// TrafficLight trafficLight3(trafficLight3Pins);
// TrafficLight trafficLight4(trafficLight4Pins);
// TrafficLight trafficLight5(trafficLight5Pins);
// TrafficLight trafficLight6(trafficLight6Pins);
// TrafficLight trafficLight7(trafficLight7Pins);
// TrafficLight trafficLight8(trafficLight8Pins);
// TrafficLight trafficLight9(trafficLight9Pins);
// TrafficLight trafficLight10(trafficLight10Pins);
// TrafficLight trafficLight11(trafficLight11Pins);
// TrafficLight trafficLight12(trafficLight12Pins);



////////////////////////////
///// DECTECTION TRAIN /////
////////////////////////////

// Déclarations des fonctions
const int inputPins[] = {34, 35, 32, 33, 25, 26, 27, 14, 17, 13, 4};
const int numPins = sizeof(inputPins) / sizeof(inputPins[0]);
bool currentStates[numPins];

unsigned long iterationCounter = 0;
bool initialized = false;
int previousStates[11];



//////////////////////////
///// FUNCTION TRAIN /////
//////////////////////////
void initializePreviousStates() {
  for (int i = 0; i < numPins; i++) {
    previousStates[i] = digitalRead(inputPins[i]);
  }
  initialized = true;
}

void printPinStatesHeader() {
  Serial.print("| ");
  for (int i = 0; i < numPins; i++) {
    Serial.print("IO");
    Serial.print(inputPins[i]);
    Serial.print(" | ");
  }
  Serial.println();
}

void printPinStates(bool states[]) {
  Serial.print("| ");
  for (int i = 0; i < numPins; i++) {
    states[i] = (digitalRead(inputPins[i]) == HIGH);
    Serial.print(states[i] ? "HIGH" : "LOW");
    Serial.print(" | ");
  }
  Serial.println();
}

bool pinStatesChanged(bool states[]) {
  bool statesChanged = false;

  for (int i = 0; i < numPins; i++) {
    if (states[i] != (digitalRead(inputPins[i]) == HIGH)) {
      states[i] = !states[i];
      statesChanged = true;
    }
  }
  return statesChanged;
}



///////////////////////////
///// SETUP PROGRAMME /////
///////////////////////////
void setup() {
  // Serial Begin
  Serial.begin(9600);
  Serial.println("Hello World");
  delay(100);

  //Init GPIO
  gpio1.begin(PCAL9535A::HardwareAddress::A000);  // 0x20 - Pins = 000  => Puce N°1
  gpio2.begin(PCAL9535A::HardwareAddress::A001);  // 0x21 - Pins = 001  => Puce N°2
  gpio3.begin(PCAL9535A::HardwareAddress::A010);  // 0x22 - Pins = 010  => Puce N°3
  gpio4.begin(PCAL9535A::HardwareAddress::A011);  // 0x23 - Pins = 011  => Puce N°4
  Serial.println("GPIO INIT");
  delay(100);

  // Initialisation des feux de signalisation
  trafficLight1.init();
  trafficLight11.init();
  // trafficLight1.init();
  // trafficLight2.init();
  // trafficLight3.init();
  // trafficLight4.init();
  // trafficLight5.init();
  // trafficLight6.init();
  // trafficLight7.init();
  // trafficLight8.init();
  // trafficLight9.init();
  // trafficLight10.init();
  // trafficLight11.init();
  // trafficLight12.init();
  Serial.println("trafficLight INIT");
  delay(100);

  // Initialisation des detecteurs de courant
  for (int i = 0; i < numPins; i++) {
    pinMode(inputPins[i], INPUT);
  }
  Serial.println("detecteurs de courant INIT");
  delay(100);


  Serial.println("---------------------------");
  Serial.println("Setup Finish");
  Serial.println("---------------------------");
  delay(100);
}

void loop() {

  if (!initialized) {
    initializePreviousStates();
    printPinStatesHeader();
  }

  delay(100);

  if (pinStatesChanged(currentStates)) {
    printPinStates(currentStates);
    if (currentStates[0] == 1) {
      trafficLight1.turnOnGreen();
    } else {
      trafficLight1.turnOnRed();
    }
    // Utilisez le tableau currentStates comme nécessaire après chaque changement d'état
  }

}