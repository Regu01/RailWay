#include <Arduino.h>
#include <AceWire.h>
#include <WiFi.h>
#include "./functions/PCAL9535A.h"
#include "./functions/CMRI/CMRI.h"


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
    {gpio1, gpio1, gpio1, {6, 7, 2}},
    {gpio1, gpio1, gpio1, {3, 4, 5}},
    {gpio1, gpio1, gpio1, {1, 0, 12}},
    {gpio1, gpio1, gpio1, {13, 14, 15}},
    {gpio1, gpio1, gpio1, {11, 10, 9}},
    {gpio1, gpio2, gpio2, {8, 14, 15}},
    {gpio2, gpio2, gpio2, {12, 13, 8}},
    {gpio2, gpio2, gpio2, {9, 10, 11}},
    {gpio2, gpio2, gpio2, {7, 6, 5}},
    {gpio2, gpio2, gpio2, {4, 2, 3}},
    {gpio2, gpio2, gpio3, {1, 0, 12}},
    {gpio3, gpio3, gpio3, {13, 14, 15}},
    {gpio3, gpio3, gpio3, {11, 10, 9}},
    {gpio3, gpio3, gpio3, {8, 7, 6}},
    // Ajoutez d'autres configurations au besoin
};

// Créez les instances TrafficLight correspondantes en utilisant une boucle
std::vector<TrafficLight> trafficLights;


///////////////////////////////////
///// GESTION TRAIN DETECTION /////
///////////////////////////////////
#include "./functions/Input/inputs.h"
Inputs inputs;




////////////////////////////////
///// SETUP WIFI CONNEXION /////
////////////////////////////////
#define TCP_PORT 9007
#define LED_BUILTIN 2

const char* ssid = "PEYON-Sebastien";
const char* password =  "12688323820980798656";

WiFiServer wifiServer(TCP_PORT);
WiFiClient jmriClient;

CMRI cmri(1, 64, 64, jmriClient); // node number, number of inputs, number of outputs, strean client






///////////////////////////
///// SETUP PROGRAMME /////
///////////////////////////
void setup() {
  // Serial Begin
  Serial.begin(9600);
  Serial.println("Hello World");
  delay(100);

  // // Init Wifi
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi..");
  // }

  // Serial.println("Connected to the WiFi network");
  // Serial.println(WiFi.localIP());

  // wifiServer.begin();
  // delay(1000);


  ///////////////////////////////////////
  ///// GESTION RETROSIGNIALISATION /////
  ///////////////////////////////////////
  // Init GPIO
  gpio1.begin(PCAL9535A::HardwareAddress::A000);  // 0x20 - Pins = 000  => Puce N°1
  gpio2.begin(PCAL9535A::HardwareAddress::A001);  // 0x21 - Pins = 001  => Puce N°2
  gpio3.begin(PCAL9535A::HardwareAddress::A010);  // 0x22 - Pins = 010  => Puce N°3
  gpio4.begin(PCAL9535A::HardwareAddress::A011);  // 0x23 - Pins = 011  => Puce N°4
  Serial.println("GPIO INIT");

  delay(100);
  for (const auto& config : trafficLightConfigs) {
    trafficLights.emplace_back(config);
  }

  for (auto& trafficLight : trafficLights) {
    trafficLight.init();
  }
  Serial.println("trafficLight INIT");
  delay(100);




  // Initialisation des detecteurs de courant
  inputs.setupInputs();
  Serial.println("detecteurs de courant INIT");
  delay(100);


  // JMRI Connexion
  // bool jmriConnected = jmriClient.connected();
  // while (!jmriConnected) {
  //   jmriClient = wifiServer.available();
  //   if (jmriClient && jmriClient.connected()) {
  //     jmriConnected = true;
  //     Serial.println("JMRI Connected");
  //   }
  // }

  Serial.println("---------------------------");
  Serial.println("Setup Finish");
  Serial.println("---------------------------");
  delay(100);
}




void loop() {

    trafficLights[0].turnOnGreen();
    delay(2000);
    trafficLights[0].turnOffAll();
    delay(1000);




  // cmri.process();



  // if (!initialized) {
  //   initializePreviousStates();
  //   printPinStatesHeader();
  // }

  // delay(100);


  // // JMRI LED TEST
  // int led = cmri.get_bit(0);
  // Serial.println(led);

  // if (led == 0) {
  //   trafficLight1.turnOnGreen();
  // }
  // else {
  //   trafficLight1.turnOnRed();
  // }

  // // JMRI SENSOR TEST
  

  // if (pinStatesChanged(currentStates)) {
    
  //   printPinStates(currentStates);
  //   cmri.set_bit(0, currentStates[0]);
  //   // if (currentStates[0] == 1) {
  //   //   trafficLight1.turnOnGreen();
  //   // } else {
  //   //   trafficLight1.turnOnRed();
  //   // }
  //   // Utilisez le tableau currentStates comme nécessaire après chaque changement d'état
  // }

}