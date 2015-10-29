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
 * JelLEDfish - Drop.h
 * ----------------------------------------
 **/
#ifndef DROP_H
#define DROP_H

#include <Arduino.h>
#include "Constants.h"

#define DROP_LEDNUM_UNUSED 31

class Drop {
public:
  unsigned int stripNum:3;
  unsigned int ledNum:5;
            
public:
  Drop();
  uint8_t isActive();
  uint8_t isStarting(uint8_t stripNum);
  void start(uint8_t stripNum);
  void advance();

private:
};

#endif // DROP_H
