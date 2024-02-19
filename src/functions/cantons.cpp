// #include <Arduino.h>


// void initializePreviousStates() {
//   for (int i = 0; i < numPins; i++) {
//     previousStates[i] = digitalRead(inputPins[i]);
//   }
//   initialized = true;
// }

// void printPinStatesHeader() {
//   Serial.print("| ");
//   for (int i = 0; i < numPins; i++) {
//     Serial.print("IO");
//     Serial.print(inputPins[i]);
//     Serial.print(" | ");
//   }
//   Serial.println();
// }

// void printPinStates(bool states[]) {
//   Serial.print("| ");
//   for (int i = 0; i < numPins; i++) {
//     states[i] = (digitalRead(inputPins[i]) == HIGH);
//     Serial.print(states[i] ? "HIGH" : "LOW");
//     Serial.print(" | ");
//   }
//   Serial.println();
// }

// bool pinStatesChanged(bool states[]) {
//   bool statesChanged = false;

//   for (int i = 0; i < numPins; i++) {
//     if (states[i] != (digitalRead(inputPins[i]) == HIGH)) {
//       states[i] = !states[i];
//       statesChanged = true;
//     }
//   }
//   return statesChanged;
// }
