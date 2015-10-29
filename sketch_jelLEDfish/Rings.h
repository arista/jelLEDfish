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
 * JelLEDfish - Rings.h
 * ----------------------------------------
 **/
#ifndef RINGS_H
#define RINGS_H

#include <Arduino.h>
#include "Constants.h"
#include "Drops.h"
#include "Rand.h"

class Rings {
private:
  Drops *drops;
  Rand *rand;
  uint64_t nextTime;
            
public:
  Rings();
  void setDrops(Drops *drops);
  void setRand(Rand *rand);
  void poll(uint64_t nowTime);

private:
  void next();
};

#endif // RINGS_H
