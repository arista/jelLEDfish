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
 * JelLEDfish - JelLEDfish.h
 * ----------------------------------------
 **/
#ifndef JELLEDFISH_H
#define JELLEDFISH_H

#include <Arduino.h>
#include "Constants.h"
#include "LedStrip8.h"
#include "Rainbow.h"
#include "Drops.h"
#include "Time.h"
#include "Rand.h"
#include "SingleDrops.h"
#include "Rings.h"
#include "Tilts.h"

class JelLEDfish {
private:
  LedStrip8 ledStrip;
  Rainbow rainbow;
  Drops drops;
  Time time;
  Rand rand;
  SingleDrops singleDrops;
  Rings rings;
  Tilts tilts;

public:
  JelLEDfish();
  void setup();
  void loop();
};

#endif // JELLEDFISH_H
