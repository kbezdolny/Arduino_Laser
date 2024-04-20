#include "display.h"
#include "reciver.h"

Reciver reciver; // Create an instance of the Reciver class

// Display works only on Arduino platform
#ifdef USE_ARDUINO
Display display; // Create an instance of the Display class
#endif


void reciveData() {
  // Your transmitted protocol here
}

void setup() {
  Serial.begin(115200); // Begin serial on port 115200

  /*---- Display setup ----*/
  #ifdef USE_ARDUINO
  display.init(); // Initializing the sender
  display.F_COLOR=RED; // Change text color to RED
  display.B_COLOR=YELLOW; // Change background text color to YELLOW
  display.displayString("<[Reciver is ready!]>"); // Display a message indicating that the reciver is ready
  #endif
  /*---- End of setup ----*/

  /*---- Reciver setup ----*/
  reciver.init(); // Initializing the reciver
  reciver.useProtocol(reciveData); // Set custom method to send data
  /*---- End of setup ----*/
}

void loop() {
  reciver.start(); // Starts the Reciver functionality.
}
