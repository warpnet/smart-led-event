#ifndef LED_h
#define LED_h

#include "Arduino.h"

#define GREEN  D6
#define BLUE   D7
#define RED    D8
#define YELLOW D1
#define WHITE  D5

#define MODE_STATIC  0
#define MODE_PULSATE 1
#define MODE_RAINBOW 2

#define PULSEDELAY 5
#define RAINBOWDELAY 30

class LED {
private:
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  uint8_t white = 0;
  uint8_t yellow = 0;
  uint8_t mode = MODE_STATIC;
  uint ticker = 0;
  short angle = 0;
  bool incpulse = false;

  void set_SineLED();
  void set_Color(uint8_t r, uint8_t g, uint8_t b);
  void debug();

  // Thank you: https://www.instructables.com/How-to-Make-Proper-Rainbow-and-Random-Colors-With-/
  const uint8_t lights[360] = {
     0,    0,    0,    0,    0,    1,    1,    2,    2,    3,
     4,    5,    6,    7,    8,    9,   11,   12,   13,   15,
    17,   18,   20,   22,   24,   26,   28,   30,   32,   35,
    37,   39,   42,   44,   47,   49,   52,   55,   58,   60,
    63,   66,   69,   72,   75,   78,   81,   85,   88,   91,
    94,   97,  101,  104,  107,  111,  114,  117,  121,  124,
   127,  131,  134,  137,  141,  144,  147,  150,  154,  157,
   160,  163,  167,  170,  173,  176,  179,  182,  185,  188,
   191,  194,  197,  200,  202,  205,  208,  210,  213,  215,
   217,  220,  222,  224,  226,  229,  231,  232,  234,  236,
   238,  239,  241,  242,  244,  245,  246,  248,  249,  250,
   251,  251,  252,  253,  253,  254,  254,  255,  255,  255,
   255,  255,  255,  255,  254,  254,  253,  253,  252,  251,
   251,  250,  249,  248,  246,  245,  244,  242,  241,  239,
   238,  236,  234,  232,  231,  229,  226,  224,  222,  220,
   217,  215,  213,  210,  208,  205,  202,  200,  197,  194,
   191,  188,  185,  182,  179,  176,  173,  170,  167,  163,
   160,  157,  154,  150,  147,  144,  141,  137,  134,  131,
   127,  124,  121,  117,  114,  111,  107,  104,  101,   97,
    94,   91,   88,   85,   81,   78,   75,   72,   69,   66,
    63,   60,   58,   55,   52,   49,   47,   44,   42,   39,
    37,   35,   32,   30,   28,   26,   24,   22,   20,   18,
    17,   15,   13,   12,   11,    9,    8,    7,    6,    5,
     4,    3,    2,    2,    1,    1,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  };

public:
  LED();
  void set_StaticColor(String hexcode);
  void set_StaticColor(uint8_t r, uint8_t g, uint8_t b);
  void set_Brightness(uint8_t v);
  void set_Warmth(uint8_t v);
  void loop();

  uint8_t get_Red();
  uint8_t get_Green();
  uint8_t get_Blue();
  uint8_t get_Brightness();
  uint8_t get_Warmth();
  uint8_t get_Mode();

  void enable_Pulsate();
  void disable_Pulsate();

  void enable_Rainbow();
  void disable_Rainbow();
};

#endif