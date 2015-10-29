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
 * JelLEDfish - Drops.cpp
 * ----------------------------------------
 *
 * Represents all of the Drops that are currently falling.  Also
 * contains the pool of "inactive" Drops that are available to
 * represent new falling drops.  The pool is managed simply by
 * scanning - whenever we want to add a new falling drop, we just do a
 * brute force search through the pool for a Drop that isn't yet
 * falling.
 *
 * For some operations, we run through all of the potential drops
 * (such as when we "render" the drops to the LedStrip).  In theory we
 * could optimize this by keeping track of the highest number drop
 * that's in use, since it's very unlikely that all drops will be in
 * use.  But for now, the performance seems to be fine just running
 * through all of the drops.
 **/
#include "Drops.h"

Drops::Drops():
  nextTime(0)
{
}

// Sets the LedStrip8
void Drops::setLedStrip(LedStrip8 *ledStrip)
{
  this->ledStrip = ledStrip;
}

// Displays the current falling drops.
void Drops::render()
{
  uint8_t dropNum;
  uint32_t color;
  Drop *drop;

  color = ledStrip->toColor(255, 255, 255, DROPS_BRIGHTNESS);
  // Search through all of the drops
  for(dropNum = 0, drop = &(drops[0]); dropNum < DROPS_MAX_COUNT; dropNum++, drop++) {
    if(drop->isActive()) {
      ledStrip->setLed(drop->stripNum, drop->ledNum, color);
    }
  }
}

// Polls to see if it's time to advance to the next state
void Drops::poll(uint64_t nowTime)
{
  if(nowTime >= nextTime) {
    advance();
    nextTime += DROPS_POLL_INTERVAL;
  }
}

// Advances all of the active drops by causing them to "fall" one more LED
void Drops::advance()
{
  uint8_t dropNum;
  Drop *drop;

  // Advance each drop (each drop knows if it's active or not)
  for(dropNum = 0, drop = &(drops[0]); dropNum < DROPS_MAX_COUNT; dropNum++, drop++) {
    drop->advance();
  }
}

// Starts a drop falling from the top of the given stripNum.  If a
// drop is already at the top, then don't add a new one
void Drops::startDrop(int stripNum)
{
  uint8_t dropNum;
  Drop *drop;

  // Search through all the drops to see if one is already starting
  for(dropNum = 0, drop = &(drops[0]); dropNum < DROPS_MAX_COUNT; dropNum++, drop++) {
    // See if the drop already is set
    if(drop->isStarting(stripNum)) {
      return;
    }
  }

  // Otherwise, search for the first inactive one and set it
  for(dropNum = 0, drop = &(drops[0]); dropNum < DROPS_MAX_COUNT; dropNum++, drop++) {
    if(!drop->isActive()) {
      drop->start(stripNum);
      break;
    }
  }

  // If no available Drop is found, then a Drop won't start.  For now
  // this should never happen (since the number of potential Drops
  // equals the number of LED's), but if we ever need to reduce the
  // pool of available Drops to save memory, things shouldn't break
  // even if Drops sometimes won't actually start.
}
