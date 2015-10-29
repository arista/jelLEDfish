/**
 * Copyright 2015 Nathan Abramson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ----------------------------------------
 * JelLEDfish - Rainbow.cpp
 * ----------------------------------------
 *
 * Slowly cycles all 240 LED's through color changes.  Our state is
 * just the value of the "starting LED" - each LED essentially
 * "advances" from that state.  So when we want to advance the entire
 * set of LED's we just increment that starting state.
 **/
#include "LedStrip8.h"
#include "Rainbow.h"

Rainbow::Rainbow():
  startingPos(0),
  brightness(255),
  nextTime(0)
{
}

// Set the LedStrip8
void Rainbow::setLedStrip(LedStrip8 *ledStrip)
{
  this->ledStrip = ledStrip;
}

// Set the brightness, 0-255
void Rainbow::setBrightness(uint8_t brightness)
{
  this->brightness = brightness;
}

// Set the current color state in the LedStrip
void Rainbow::render()
{
  uint8_t stripNum, ledNum;
  uint8_t pos;
  uint32_t color;

  pos = startingPos;
  for(stripNum = 0; stripNum < 8; stripNum++) {
    for(ledNum = 0; ledNum < 30; ledNum++) {
      color = colorFromPos(pos++);
      ledStrip->setLed(stripNum, ledNum, color);
    }
  }
}

// See if it's time to advance to the next color state
void Rainbow::poll(uint64_t nowTime)
{
  if(nowTime >= nextTime) {
    advance();
    nextTime += RAINBOW_POLL_INTERVAL;
  }
}

// Advance to the next color state
void Rainbow::advance()
{
  startingPos++;
}

// Generates a color from a single byte.  Based on the Florabrella
// code (https://learn.adafruit.com/florabrella/code).  As the "pos"
// ranges from 0-255, it cycles from red, to green, to blue, then back
// to red.
uint32_t Rainbow::colorFromPos(uint8_t pos)
{
  if(pos < 85) {
    return ledStrip->toColor(255 - pos * 3, pos * 3, 0, brightness);
  }
  else if(pos < 170) {
    pos -= 85;
    return ledStrip->toColor(0, 255 - pos * 3, pos * 3, brightness);
  }
  else {
    pos -= 170;
    return ledStrip->toColor(pos * 3, 0, 255 - pos * 3, brightness);
  }
}

