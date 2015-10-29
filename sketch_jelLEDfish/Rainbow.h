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
 * JelLEDfish - Rainbow.h
 * ----------------------------------------
 **/
#ifndef RAINBOW_H
#define RAINBOW_H

#include <Arduino.h>
#include "Constants.h"

class Rainbow {
private:
  LedStrip8 *ledStrip;
  uint8_t startingPos;
  uint8_t brightness;
  uint64_t nextTime;
            
public:
  Rainbow();
  void setLedStrip(LedStrip8 *ledStrip);
  void setBrightness(uint8_t brightness);
  void render();
  void poll(uint64_t nowTime);

private:
  uint32_t colorFromPos(uint8_t pos);
  void advance();
};

#endif // RAINBOW_H
