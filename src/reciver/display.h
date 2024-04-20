#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <Arduino.h>

// Connect data pins LCD_D 0-7 to arduino UNO:
// LCD_D 0 -- D8
// LCD_D 1 -- D9
// LCD_D 2 -- D2
// LCD_D 3 -- D3
// LCD_D 4 -- D4
// LCD_D 5 -- D5
// LCD_D 6 -- D6
// LCD_D 7 -- D7
// Connect command pins:
// LCD_RST -- A4   1 -> 0 min 15 micros 0 -> 1 
// LCD_CS  -- A3   chip select, aktiv LOW
// LCD_RS  -- A2   data/command select, 0 command, 1 data
// LCD_WR  -- A1   0 -> 1, HIGH when not used
// LCD_RD  -- A0   0 -> 1, HIGH when not used

// arduino uno porty:
// B (digital pin 8 to 13) 
// C (analog input pins) 
// D (digital pins 0 to 7)   0 1 are RX TX, don't use 

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Touchscreen connection:
#define Y1 A3
#define X1 A2
#define Y2 9
#define X2 8

/*!
  @brief Class for controlling a display.
  @details This class provides methods for initializing the display, drawing shapes, displaying text, and more.
 */
class Display {
public:
  /*! Gap between simbols */
  int16_t COL_GAP=4;
  /*! LCD horizontal cursor pointer */
  int16_t P_COL=COL_GAP;
  /*! LCD vertical cursor pointer */
  int16_t P_ROW=2;

  /*! Font size */
  uint8_t F_SIZE=2;
  /*! Foreground color */
  uint16_t F_COLOR=BLACK;
  /*! Background color */
  uint16_t B_COLOR=WHITE;

  /*!
    @brief Initialize the display.
   */
  void init();

  /*!
    @brief Draw a rectangle on the display.
    @param col The column position of the top-left corner of the rectangle.
    @param row The row position of the top-left corner of the rectangle.
    @param width The width of the rectangle.
    @param height The height of the rectangle.
    @param color The color of the rectangle.
   */
  void rect(int16_t col, int16_t row, int16_t width, int16_t height, int16_t color);

  /*!
    @brief Clear the display.
    @param color The color to fill the display with.
   */
  void clear(byte color = WHITE);

  /*!
    @brief Display an integer value on the screen.
    @param n The integer value to display.
   */
  void displayInteger(int16_t n);

  /*!
    @brief Display a string on the screen.
    @param str The string to display.
   */
  void displayString(String str);

  /*!
    @brief Display a single character on the screen.
    @param simbol The character to display.
   */
  void displayChar(char simbol);

  /*!
    @brief Clear a specified number of characters from the display.
    @param n The number of characters to clear.
   */
  void clearChars(byte n);

  /*!
    @brief Move the cursor to the next line on the display.
   */
  void newLine();

private:
  // TS calibration
  uint16_t ROW_F=110; // TS first row
  uint16_t ROW_L=920; // TS last row
  uint16_t COL_F=110; // TS first column
  uint16_t COL_L=930; // TS last column

  // draw keypad
  String K_LABEL[11] = {"1","2","3","4","5","6","7","8","9","0","<"};
  uint16_t K_ROW[11]  = {150,150,150,100,100,100,50,50,50,200,200};
  uint16_t K_COL[11]  = {10,50,90,10,50,90,10,50,90,50,90};

  void write(uint8_t d);
  void writeCommand(uint8_t d);
  void writeData(uint8_t d);
  uint8_t read();
  void setPortAsInput();
  void setPortAsOutput();
};

#endif
