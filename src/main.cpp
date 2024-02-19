#include <Arduino.h>
#include <AceWire.h>
#include "./functions/PCAL9535A.h"


///////////////////////////////////////
///// GESTION RETROSIGNIALISATION /////
///////////////////////////////////////
#include "./functions/Output/outputs.h"
#include <vector>

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

// Tableau de configurations pour les feux de signalisation
const TrafficLight::GpioColors trafficLightConfigs[] = {
    {gpio1, gpio1, gpio1, {6, 7, 2}, "TrafficLight1"},
    {gpio1, gpio1, gpio1, {3, 4, 5}, "TrafficLight2"},
    {gpio1, gpio1, gpio1, {1, 0, 12}, "TrafficLight3"},
    {gpio1, gpio1, gpio1, {13, 14, 15}, "TrafficLight4"},
    {gpio1, gpio1, gpio1, {11, 10, 9}, "TrafficLight5"},
    {gpio1, gpio2, gpio2, {8, 14, 15}, "TrafficLight6"},
    {gpio2, gpio2, gpio2, {12, 13, 8}, "TrafficLight7"},
    {gpio2, gpio2, gpio2, {9, 10, 11}, "TrafficLight8"},
    {gpio2, gpio2, gpio2, {7, 6, 5}, "TrafficLight9"},
    {gpio2, gpio2, gpio2, {4, 2, 3}, "TrafficLight10"},
    {gpio2, gpio2, gpio3, {1, 0, 12}, "TrafficLight11"},
    {gpio3, gpio3, gpio3, {13, 14, 15}, "TrafficLight12"},
    {gpio3, gpio3, gpio3, {11, 10, 9}, "TrafficLight13"},
    {gpio3, gpio3, gpio3, {8, 7, 6}, "TrafficLight14"},
    // Ajoutez d'autres configurations au besoin
};

// Créez les instances TrafficLight correspondantes en utilisant une boucle
std::vector<TrafficLight> trafficLights;

// Initialisation des composants
void initializeComponentsTrafficLight() {
  // Initialisation des GPIOs
  gpio1.begin(PCAL9535A::HardwareAddress::A000);  // 0x20 - Pins = 000  => Puce N°1
  gpio2.begin(PCAL9535A::HardwareAddress::A001);  // 0x21 - Pins = 001  => Puce N°2
  gpio3.begin(PCAL9535A::HardwareAddress::A010);  // 0x22 - Pins = 010  => Puce N°3
  gpio4.begin(PCAL9535A::HardwareAddress::A011);  // 0x23 - Pins = 011  => Puce N°4
  delay(100);

  // Initialisation des feux de signalisation
  for (const auto& config : trafficLightConfigs) {
    trafficLights.emplace_back(config);
  }
  // Initialisation des feux de signalisation to low
  for (auto& trafficLight : trafficLights) {
    trafficLight.init();
  }

  Serial.println("Initialize Components TrafficLight : INIT");
  delay(100);

}



///////////////////////////////////
///// GESTION TRAIN DETECTION /////
///////////////////////////////////
#include "./functions/Input/inputs.h"

// Tableau de configurations pour les cantons
const Canton::CantonPins cantonConfigs[] = {
    {34},{35},{32},{33},{25},{26},{27},{14},{17},{13},{4},
};

// Créez les instances Canton correspondantes en utilisant une boucle
std::vector<Canton> cantons;


// Initialisation des composants
void initializeComponentsCanton() {
  // Initialisation des détecteurs de courant
  for (const auto& config : cantonConfigs) {
      cantons.emplace_back(config);
  }
  // Initialisez tous les cantons
  for (auto& canton : cantons) {
      canton.init();
  }

  Serial.println("Initialize Components Canton : INIT");
  delay(100);
}








// Initialisation du programme
void setup() {
  Serial.begin(9600);
  Serial.println(" ");
  delay(100);
  Serial.println("---------------------------");
  Serial.println("Setup Start");
  Serial.println("---------------------------");
  delay(100);

  Serial.println("---------------------------");
  initializeComponentsTrafficLight();
  initializeComponentsCanton();
  Serial.println("---------------------------");
  delay(100);

  Serial.println("---------------------------");
  Serial.println("Setup Finish");
  Serial.println("---------------------------");
  delay(100);
}



void loop() {
  Serial.println("---------------------------");
  Serial.println("Loop Start");
  Serial.println("---------------------------");
  delay(100);
  // trafficLights[0].turnOffAll();
  // for (const auto& canton : cantons) {
  //   bool state = canton.readDigitalInput();
  //   Serial.print("Canton Pin ");
  //   Serial.print(canton.getPin());
  //   Serial.print(" State: ");
  //   Serial.println(state ? "HIGH" : "LOW");
  // }

  delay(100000);
}
