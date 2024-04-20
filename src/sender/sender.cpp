#include "sender.h"
#include "Arduino.h"

void Sender::init() {
  pinMode(btnPin, INPUT); // Analog pin
  pinMode(laserPin, OUTPUT); // Digital pin
  digitalWrite(laserPin, LOW); // Disable laser
}

void Sender::charToBinary(char c, byte binary[8]) {
  for (int i = 0; i < 8; i++) {
    binary[i] = (c & (1 << i)) ? 1 : 0;
  }
}

void Sender::setTransmittedData(const String data[5]) {
  for (int i = 0; i < 5; ++i) {
    transmittedData[i] = data[i];
  }
}

void Sender::setButtonThreshold(int16_t threshold) {
  if (threshold < 0) {
    return;
  }
  btnThreshold = threshold;
}

void Sender::checkKeyboard(int16_t value) {
  if (value <= btnValue1) {
    Sender::changeTransmittedTextTo(0);
  }
  else if (value <= btnValue2) {
    Sender::changeTransmittedTextTo(1);
  }
  else if (value <= btnValue3) {
    Sender::changeTransmittedTextTo(2);
  }
  else if (value <= btnValue4) {
    Sender::changeTransmittedTextTo(3);
  }
  else if (value <= btnValue5) {
    Sender::changeTransmittedTextTo(4);
  }
}

bool Sender::isKeyboardButtonPressed(unsigned long currentMillis, unsigned long previousMillis, int16_t btnValue) {
  return 
    btnValue > btnThreshold 
    && currentMillis - previousMillis > debounceDelay;
}

void Sender::start() {
  unsigned long previousMillis = 0;

  while (1) {
    unsigned long currentMillis = millis();
    int btnValue = analogRead(btnPin);
    if (isKeyboardButtonPressed(currentMillis, previousMillis, btnValue)) {
      checkKeyboard(btnValue);
      protocolMethod();
      previousMillis = currentMillis;
    }
  }
}
