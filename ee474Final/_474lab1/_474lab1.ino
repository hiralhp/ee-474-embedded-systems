// IMPORTANT: ELEGOO_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Elegoo_TFTLCD.h FOR SETUP.
//Technical support:goodtft@163.com

#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Elegoo_TFTLCD tft;



// Run setup before loop executes.
void setup(void) {
  Serial.begin(9600);                   // Baud rate: bits sent per second.
  Serial.println(F("TFT LCD test"));    // Test LCD display. Print on LCD screen.

// Determines if USE_Elegoo_SHIELD_PINOUT is defined. Prints out which pinout is being used.
#ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.4\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Elegoo 2.4\" TFT Breakout Board Pinout"));
#endif

  // Prints out information about LCD screen.
  Serial.print("TFT size is ");
  Serial.print(tft.width());            // Prints out LCD screen width.
  Serial.print("x");
  Serial.println(tft.height());         // Prints out LCD screen height.

  tft.reset();                          // Resets LCD screen.

  // Determines and prints out which LCD driver is being used.
   uint16_t identifier = tft.readID();  // Read LCD ID.
   if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  }
  // Redefine drivers.
  else if(identifier==0x0101)
  {
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }
  else if(identifier==0x1111)
  {
      identifier=0x9328;
       Serial.println(F("Found 0x9328 LCD driver"));
  }
  // Error messages and handling.
  else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9328;                  // Default to ILI9328 LCD driver

  }
  tft.begin(identifier);                // Initializes LCD screen with LCD driver.
}

  int i=0;                              // Iteration variable.
  char myArray[10];                     // Char array a.k.a. strings

// Execute main program
void loop(void)                         // Continous loop. Run forever.
{
  tft.fillScreen(BLACK);                // Turns screen black.
  unsigned long start = micros();       // Record how long Arduino has been running program.
  tft.setCursor(0, 0);                  // Sets the coordinates of the starting point of printing texts on the TFT screen.

  tft.setTextColor(GREEN);              // Set text color to green.
  tft.setTextSize(2);                   // Set text size to 2 (height: 20 pixels)

  // Store numbers 48...57 in array.
  for (i = 0; i <=9; i++)
  {
    myArray[i]= 48+i;
  }

  // Prints numbers 57...48 on LCD screen at one second rate.
  for (i = 9; i >= 0; i--)
  {
    tft.print(myArray[i]);
    delay(1000);
  }

  // Delay for three seconds.
  delay(1000);
  delay(1000);
  delay(1000);
}

