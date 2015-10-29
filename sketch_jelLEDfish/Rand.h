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
 * JelLEDfish - Rand.h
 * ----------------------------------------
 **/
#ifndef RAND_H
#define RAND_H

#include <Arduino.h>
#include "Constants.h"

class Rand {
private:
  uint32_t next;
            
public:
  Rand();
  uint32_t generate();
  uint32_t generateRange(uint32_t low, uint32_t high);

private:
  uint32_t seed();
};

#endif // RAND_H
