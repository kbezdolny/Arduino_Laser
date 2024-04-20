#include "sender.h"

Sender sender; // Create an instance of the Sender class

void sendData() {
  // Your transmitted protocol here
}

void setup() {
  Serial.begin(115200); // Begin serial on port 115200

  /*---- Sender setup ----*/
  sender.init(); // Initializing the sender
  String newData[] = 
    { "Data 1", "Data 2", "Data 3", "Data 4", "Data 5" }; // Custom transmitted data
  sender.setTransmittedData(newData); // Set custom transmitted data
  sender.useProtocol(sendData); // Set custom method to send data
  /*---- End of setup ----*/
}

void loop() {
  sender.start(); // Starts the Sender functionality.
}
