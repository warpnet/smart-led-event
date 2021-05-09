#define DEBUG true

#include "LED.h"

LED::LED() {
  // Initialize the pin's as output.
  pinMode(RED,    OUTPUT);
  pinMode(GREEN,  OUTPUT);
  pinMode(BLUE,   OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(WHITE,  OUTPUT);
}

void LED::set_StaticColor(String hexcode) {
  // Example: #010203
  if (hexcode.length() == 7) {
    int number = (int) strtol( &hexcode[1], NULL, 16);
    int r = number >> 16;
    int g = number >> 8 & 0xFF;
    int b = number & 0xFF;

    this->set_StaticColor(r, g, b);
  }
}

void LED::set_StaticColor(uint8_t r, uint8_t g, uint8_t b) {
  this->disable_Rainbow();
  this->set_Color(r, g, b);
}

void LED::set_Color(uint8_t r, uint8_t g, uint8_t b) {
  this->red = r;
  this->green = g;
  this->blue = b;

  analogWrite(RED,   this->red);
  analogWrite(GREEN, this->green);
  analogWrite(BLUE,  this->blue);
}

void LED::set_Brightness(uint8_t v) {
  this->white = v;
  analogWrite(WHITE,  this->white);
}

void LED::set_Warmth(uint8_t v) {
  this->yellow = v;
  analogWrite(YELLOW, this->yellow);
}

uint8_t LED::get_Red() {return this->red;}
uint8_t LED::get_Green() {return this->green;}
uint8_t LED::get_Blue() {return this->blue;}
uint8_t LED::get_Brightness() {return this->white;}
uint8_t LED::get_Warmth() {return this->yellow;}
uint8_t LED::get_Mode() {return this->mode;}

void LED::loop() {
  this->ticker++;

  if ((this->mode & MODE_PULSATE) > 0) {
    if ((this->ticker % (PULSEDELAY * 100)) == 0) {
      if (this->get_Warmth() >= 255 || this->get_Warmth() <= 0) {
        this->incpulse = !this->incpulse;
      }
      if (this->incpulse) {
        this->set_Warmth(this->get_Warmth()+1);
      }
      else {
        this->set_Warmth(this->get_Warmth()-1);
      }
    }
  }

  if ((this->mode & MODE_RAINBOW) > 0) {
    if ((this->ticker % (RAINBOWDELAY * 100)) == 0) {
      if (this->angle < 360) {
        this->angle++;
      } else {
        this->angle = 0;
      }
      this->set_SineLED();
    }

  }

  #ifdef DEBUG
    if ((this->ticker % (100 * 100)) == 0) {
      this->debug();
  }
  #endif
}

void LED::set_SineLED() {
  uint8_t r = this->lights[(this->angle + 120) % 360];
  uint8_t g = this->lights[this->angle];
  uint8_t b = this->lights[(this->angle + 240) % 360];
  this->set_Color(r, g, b);
}

void LED::debug() {
  String msg = "R,G,B,W,Y,Mode: ";
  msg += String(this->red, HEX);
  msg += ",";
  msg += String(this->green, HEX);
  msg += ",";
  msg += String(this->blue, HEX);
  msg += ",";
  msg += String(this->white, HEX);
  msg += ",";
  msg += String(this->yellow, HEX);
  msg += ",";
  msg += String(this->mode, HEX);
  Serial.println(msg);
}

void LED::enable_Pulsate() {
  if (this->get_Warmth() >= 255) {
    this->incpulse = false;
  }
  else {
    this->incpulse = true;
  }
  this->mode |= MODE_PULSATE;
}

void LED::disable_Pulsate() {
  this->mode &= ~MODE_PULSATE;
}

void LED::enable_Rainbow() {
  this->mode |= MODE_RAINBOW;
}

void LED::disable_Rainbow() {
  this->mode &= ~MODE_RAINBOW;
}