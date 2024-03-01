#include <Arduino.h>
#include <AceWire.h>
#include <AceButton.h>
#include "./functions/PCAL9535A.h"

const char *boardName = "BoardESP1";

//https://github.com/bxparks/AceButton/blob/develop/examples/ArrayButtons/ArrayButtons.ino
using namespace ace_button;

// Number of canton
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