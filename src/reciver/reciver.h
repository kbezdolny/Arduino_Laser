#ifndef RECIVER_H_INCLUDED
#define RECIVER_H_INCLUDED

//#define USE_ESP
#define USE_ARDUINO

#include <Arduino.h>

// Type for function pointer
typedef void (*FunctionPointer)();

/*!
  @brief   Class for recive data.
  @details This class handles the functionality related to recive data from a laser signal.
*/
class Reciver {
  public:
    /*!
      @brief   Initializes the receiver object.
      @details Sets up the pin modes.
    */
    void init();

    /*!
      @brief   Starts the receiver.
    */
    void start();

    /*!
      @brief   Sets the protocol to be used.
      @param   function A function pointer to the protocol method.
    */
    void useProtocol(FunctionPointer function) { protocolMethod = function; }

    /*!
      @brief   Retrieves the signal from the receiver pin.
      @return  The signal strength.
    */
    int getSignal() { return analogRead(receivePin); }

    /*!
      @brief   Converts an array of bits to a character.
      @param   binaries An array of 8 bits representing a character.
      @return  The converted character.
    */
    char binaryToChar(byte binaries[8]);

  private:
    // Pin for receiving signals
    #ifdef USE_ESP
    const int8_t receivePin = 15;
    #endif

    #ifdef USE_ARDUINO
    const int8_t receivePin = A5;
    #endif

    // Pointer to the protocol method
    FunctionPointer protocolMethod;
};

#endif