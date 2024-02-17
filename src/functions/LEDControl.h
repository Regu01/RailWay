// LEDControl.h
#define LED_CONTROL_H

#include <AceWire.h>
#include "./functions/PCAL9535A.h"
using ace_wire::SimpleWireInterface;

extern PCAL9535A::PCAL9535A<SimpleWireInterface> gpio3;
extern PCAL9535A::PCAL9535A<SimpleWireInterface> gpio4;

void turnAllLedsOn(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio);
void turnAllLedsOff(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio);
void invertAllPins(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio);
void setLedStates(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio, uint16_t ledStates);
uint16_t getAllPortStates(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio);
uint8_t getPortState(PCAL9535A::PCAL9535A<ace_wire::SimpleWireInterface>& gpio, PCAL9535A::Port port);