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
 * JelLEDfish - LedStrip8.h
 * ----------------------------------------
 **/
#ifndef LEDSTRIP8_H
#define LEDSTRIP8_H

#include <Arduino.h>
#include "Constants.h"

class LedStrip8 {
private:
  // Each byte holds the data values for the LED's on multiple strips.
  // For example [3][0] holds high green bit for the third LED on all
  // 8 strips (well, strips 0-5 for portBData and strips 6-7 for
  // portDData)
  
  // Stored as [ledNum][24 bits/led for multiple strips]
  uint8_t portBData[30][24];
  uint8_t portDData[30][24];
            
public:
  LedStrip8();
  void clear();
  void setLed(uint8_t stripNum, uint8_t ledNum, uint32_t grb);
  void show();
  uint32_t toColor(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);

private:
  uint32_t adjustBrightness(uint8_t val, uint8_t brightness);
  
};

#endif // LEDSTRIP8_H
