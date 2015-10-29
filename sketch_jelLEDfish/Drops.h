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
 * JelLEDfish - Drops.h
 * ----------------------------------------
 **/
#ifndef DROPS_H
#define DROPS_H

#include <Arduino.h>
#include "Constants.h"
#include "Drop.h"
#include "LedStrip8.h"

// Hard-coded to the maximum number of LED's that might be falling
// at one time (8 strips, 30 LED's per strip)
#define DROPS_MAX_COUNT 240

class Drops {
private:
  LedStrip8 *ledStrip;
  Drop drops[DROPS_MAX_COUNT];
  uint64_t nextTime;
            
public:
  Drops();
  void setLedStrip(LedStrip8 *ledStrip);
  void render();
  void poll(uint64_t nowTime);
  void startDrop(int stripNum);

private:
  void advance();
};

#endif // DROPS_H
