#ifndef SENDER_H_INCLUDED
#define SENDER_H_INCLUDED

//#define USE_ESP
#define USE_ARDUINO

#include "Arduino.h"

typedef void (*FunctionPointer)();

/*!
  @brief   Class for sending data.
  @details This class handles the functionality related to sending data using a laser.
*/
class Sender {
  public:
    /*!
      @brief   Initializes the Sender object.
      @details Sets the input/output modes for button and laser pins.
    */
    void init();

    /*!
      @brief   Sets the function for sending data.
      @param   function Pointer to the function that will be called to send data.
    */
    void useProtocol(FunctionPointer function) { protocolMethod = function; }

    /*!
      @brief   Write signal to laser pin
      @param   signal HIGH(1) or LOW(0) 
    */
    void sendSignal(byte signal) { digitalWrite(laserPin, signal); }

    /*!
      @brief   Converts a character to binary format.
      @param   c Character to convert.
      @param   binary Array to store the binary representation of the character (size 8).
    */
    void charToBinary(char c, byte binary[8]);

    /*!
      @brief   Sets the array of strings to be transmitted.
      @param   data Array of strings to be transmitted.
    */
    void setTransmittedData(const String data[5]);

    /*!
      @brief   Gets the current transmitted text.
      @return  Current transmitted text.
    */
    String getTransmittedText() { return transmittedText; }

    /*!
      @brief   Sets the button threshold for detecting button presses.
      @param   threshold Threshold value for a pressed button.
    */
    void setButtonThreshold(int16_t threshold);

    /*!
      @brief   Starts the Sender functionality.
    */
    void start();

  private:
    #ifdef USE_ESP
    const int8_t laserPin = 4; // (digital) laser OUTPUT pin 
    const int8_t btnPin = 16; // (analog) Button INPUT pin 
    #endif

    
    #ifdef USE_ARDUINO
    const int8_t laserPin = 2; // (digital) laser OUTPUT pin 
    const int8_t btnPin = A0; // (analog) Button INPUT pin 
    #endif
    
    FunctionPointer protocolMethod;

    /*--- Keyboard settings ---*/
    const int16_t btnValue1 = 210; // Button 1 -> 'Message 1'
    const int16_t btnValue2 = 406; // Button 2 -> 'Message 2'
    const int16_t btnValue3 = 611; // Button 3 -> 'Message 3'
    const int16_t btnValue4 = 816; // Button 4 -> 'Message 4'
    const int16_t btnValue5 = 1023; // Button 5 -> 'Message 5'
    const int16_t debounceDelay = 400; // (ms) Time to prevent button blocking
    int16_t btnThreshold = 50; // 50 - minimum threshold for a pressed button (this value can be changed)

    String transmittedData[5] = { "Message 1", "Message 2", "Message 3", "Message 4", "Message 5" };
    String transmittedText = transmittedData[0];

    /*!
      @brief   Changes the transmitted text based on the index.
      @param   index Index of the message in the transmitted data array.
    */
    void changeTransmittedTextTo(int8_t index) { transmittedText = transmittedData[index]; }

    /*!
      @brief   Checks the keyboard button pressed and updates the transmitted text accordingly.
      @param   value Value read from the button input.
    */
    void checkKeyboard(int16_t value);

    /*!
      @brief   Checks if a keyboard button is pressed.
      @param   currentMillis Current time in milliseconds.
      @param   previousMillis Time when the last button press occurred.
      @param   btnValue Value read from the button input.
      @return  True if a button is pressed, false otherwise.
    */
    bool isKeyboardButtonPressed(unsigned long currentMillis, unsigned long previousMillis, int16_t btnValue);
};

#endif // SENDER_H_INCLUDED