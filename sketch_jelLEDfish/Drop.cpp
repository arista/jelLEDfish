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
 * JelLEDfish - Drop.cpp
 * ----------------------------------------
 *
 * Represents one white "drop" that is "falling" down one of the
 * strips.  The drop keeps track of which strip it's falling down, and
 * where it is currently on the strip (0-29, 0 being the top).  If its
 * position is the special value DROP_LEDNUM_UNUSED, then it's not
 * currently falling, and is available for being allocated to
 * represent a new falling drop.
 **/
#include "Drop.h"

Drop::Drop():
  stripNum(0),
  ledNum(DROP_LEDNUM_UNUSED)
{
}

// Returns true if this Drop is actively falling
uint8_t Drop::isActive()
{
  return ledNum != DROP_LEDNUM_UNUSED;
}

// Returns true if this Drop is just starting to fall down the given
// strip
uint8_t Drop::isStarting(uint8_t stripNum)
{
  return this->stripNum == stripNum && this->ledNum == 0;
}

// Starts this drop falling down the given strip
void Drop::start(uint8_t stripNum)
{
  this->stripNum = stripNum;
  ledNum = 0;
}

// Advances this drop one step in falling (if it's active)
void Drop::advance()
{
  if(isActive()) {
    ledNum++;
    if(ledNum >= 30) {
      ledNum = DROP_LEDNUM_UNUSED;
    }
  }
}

