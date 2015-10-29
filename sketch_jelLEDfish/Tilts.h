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
 * JelLEDfish - Tilts.h
 * ----------------------------------------
 **/
#ifndef TILTS_H
#define TILTS_H

#include <Arduino.h>
#include "Constants.h"
#include "Drops.h"

// FIXME - use an enum?
#define TILTDIR_NONE 0
#define TILTDIR_N 1
#define TILTDIR_NE 2
#define TILTDIR_E 3
#define TILTDIR_SE 4
#define TILTDIR_S 5
#define TILTDIR_SW 6
#define TILTDIR_W 7
#define TILTDIR_NW 8

class Tilts {
private:
  Drops *drops;
            
public:
  Tilts();
  void setDrops(Drops *drops);
  void poll();

private:
  uint8_t tiltDir();
};

#endif // TILTS_H
