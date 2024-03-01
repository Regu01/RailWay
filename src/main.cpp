#include <Arduino.h>
#include <vector>
#include <AceWire.h>
#include <AceButton.h>
#include "./functions/PCAL9535A.h"
#include "./functions/TRAFFIC_LIGHT/TRAFFIC_LIGHT.h"

const char *boardName = "BoardESP1";

///////////////////////////////////////
///// GESTION RETROSIGNIALISATION /////
///////////////////////////////////////
using ace_wire::SimpleWireInterface;

// SimpleWireInterface (PIN_SDA, PIN_SCL, DELAY_MICROS)
SimpleWireInterface wire(21, 22, 1);

// Create PCAL9535A instance with reference to SimpleWireInterface
PCAL9535A::PCAL9535A<SimpleWireInterface> gpio1(wire);
PCAL9535A::PCAL9535A<SimpleWireInterface> gpio2(wire);
PCAL9535A::PCAL9535A<SimpleWireInterface> gpio3(wire);
PCAL9535A::PCAL9535A<SimpleWireInterface> gpio4(wire);

// Tableau de configurations pour les feux de signalisation
const TrafficLight::GpioColors trafficLightConfigs[] = {
    {gpio1, gpio1, gpio1, {6, 7, 2}, "TRAFFIC_LIGHT_"},
    {gpio1, gpio1, gpio1, {3, 4, 5}, "TRAFFIC_LIGHT_2"},
    {gpio1, gpio1, gpio1, {1, 0, 12}, "TRAFFIC_LIGHT_3"},
    {gpio1, gpio1, gpio1, {13, 14, 15}, "TRAFFIC_LIGHT_4"},
    {gpio1, gpio1, gpio1, {11, 10, 9}, "TRAFFIC_LIGHT_5"},
    {gpio1, gpio2, gpio2, {8, 14, 15}, "TRAFFIC_LIGHT_6"},
    {gpio2, gpio2, gpio2, {12, 13, 8}, "TRAFFIC_LIGHT_7"},
    {gpio2, gpio2, gpio2, {9, 10, 11}, "TRAFFIC_LIGHT_8"},
    {gpio2, gpio2, gpio2, {7, 6, 5}, "TRAFFIC_LIGHT_9"},
    {gpio2, gpio2, gpio2, {4, 2, 3}, "TRAFFIC_LIGHT_10"},
    {gpio2, gpio2, gpio3, {1, 0, 12}, "TRAFFIC_LIGHT_11"},
    {gpio3, gpio3, gpio3, {13, 14, 15}, "TRAFFIC_LIGHT_12"},
    {gpio3, gpio3, gpio3, {11, 10, 9}, "TRAFFIC_LIGHT_13"},
    {gpio3, gpio3, gpio3, {8, 7, 6}, "TRAFFIC_LIGHT_14"},
};

// Créez les instances TrafficLight correspondantes en utilisant une boucle
std::vector<TrafficLight> trafficLights;







///////////////////////////////
///// GESTION DES CANTONS /////
///////////////////////////////
// https://github.com/bxparks/AceButton/blob/develop/examples/ArrayButtons/ArrayButtons.ino
using namespace ace_button;

const uint8_t NUM_CANTON = 12;

struct Info
{
    const uint8_t pin;
    const char *name;
};

Info CANTONS[NUM_CANTON] = {
    {34, "CANTON_1"},
    {35, "CANTON_2"},
    {32, "CANTON_3"},
    {33, "CANTON_4"},
    {25, "CANTON_5"},
    {26, "CANTON_6"},
    {27, "CANTON_7"},
    {14, "CANTON_8"},
    {17, "CANTON_9"},
    {13, "CANTON_10"},
    {15, "CANTON_11"},
    {4, "CANTON_12"},
};

AceButton cantons[NUM_CANTON];

// Forward reference to prevent Arduino compiler becoming confused.
void handleEvent(AceButton *, uint8_t, uint8_t);









// Initialisation des composants
void initializeComponentsTrafficLight()
{
    // Initialisation des GPIOs
    gpio1.begin(PCAL9535A::HardwareAddress::A000); // 0x20 - Pins = 000  => Puce N°1
    gpio2.begin(PCAL9535A::HardwareAddress::A001); // 0x21 - Pins = 001  => Puce N°2
    gpio3.begin(PCAL9535A::HardwareAddress::A010); // 0x22 - Pins = 010  => Puce N°3
    gpio4.begin(PCAL9535A::HardwareAddress::A011); // 0x23 - Pins = 011  => Puce N°4
    delay(100);

    // Initialisation des feux de signalisation
    for (const auto &config : trafficLightConfigs)
    {
        trafficLights.emplace_back(config);
    }
    // Initialisation des feux de signalisation to low
    for (auto &trafficLight : trafficLights)
    {
        trafficLight.init();
        trafficLight.turnOnAll();
    }
}

void initializeComponentsCanton()
{
    for (uint8_t i = 0; i < NUM_CANTON; i++)
    {
        // Button uses the built-in pull up register.
        pinMode(CANTONS[i].pin, INPUT_PULLUP);
        // initialize the corresponding AceButton.
        cantons[i].init(CANTONS[i].pin, HIGH, i);
    }

    // Configure the ButtonConfig with the event handler, and enable all higherlevel events.
    ButtonConfig *buttonConfig = ButtonConfig::getSystemButtonConfig();
    buttonConfig->setEventHandler(handleEvent);
    buttonConfig->setFeature(ButtonConfig::kFeatureClick);
    buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
    buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
    buttonConfig->setFeature(ButtonConfig::kFeatureRepeatPress);
}






void setup()
{
    delay(1000);
    Serial.begin(9600);
    while (!Serial)
        ;
    Serial.println(F(""));
    Serial.println(F("setup(): begin"));

    initializeComponentsCanton();
    initializeComponentsTrafficLight();

    Serial.println(F("setup(): ready"));
}

void loop()
{
    // Should be called every 4-5ms or faster, for the default debouncing time of ~20ms.
    for (uint8_t i = 0; i < NUM_CANTON; i++)
    {
        cantons[i].check();
    }
}






// The event handler for the canton.
void handleEvent(AceButton *cantons, uint8_t eventType, uint8_t cantonState)
{
    // Get the canton info
    uint8_t id = cantons->getId();

    // Create a string to store the message
    String eventMessage = F("handleEvent(): ");
    eventMessage += boardName;
    eventMessage += F("; eventType: ");
    eventMessage += AceButton::eventName(eventType);
    eventMessage += F("; cantonName: ");
    eventMessage += CANTONS[id].name;
    eventMessage += F("; cantonState: ");
    eventMessage += cantonState;

    // Print the message
    Serial.println(eventMessage);

    switch (eventType)
    {
    case AceButton::kEventPressed:
        //   Train in cantons
        break;
    case AceButton::kEventLongPressed:
        //   Train in cantons validate
        break;
    case AceButton::kEventRepeatPressed:
        //   Train power bad
        break;
    case AceButton::kEventReleased:
        //   Train out cantons
        break;
    case AceButton::kEventLongReleased:
        //   Train out cantons validate
        break;
    }
}