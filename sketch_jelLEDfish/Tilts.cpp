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
 * JelLEDfish - Tilts.cpp
 * ----------------------------------------
 *
 * Reads the state of the 4 tilt switches, and continually sends drops
 * down two strips depending on the direction (making it look like
 * that "tentacle" is lighting up).  Stops sending drops if the
 * direction changes (or there is no tilting).
 *
 * The strips are assumed to be arranged as if the 8 points of a
 * tic-tac-toe board, which naturally leads to two strips representing
 * each of the 8 directions.
 *
 * Because we don't necessarily know which strips are which until we
 * assemble it, we keep a lookup table to map "strip order" to the
 * actual strips.
 **/
#include "Tilts.h"

Tilts::Tilts()
{
}

void Tilts::setDrops(Drops *drops)
{
  this->drops = drops;
}

// The order of the strips, starting from front right, going clockwise
// (looking down)
int stripOrder[] = STRIP_ORDER;

// Determine what direction the costume is tilted and start sending
// drops down the appropriate strips
void Tilts::poll()
{
  uint8_t val = PIND;

  uint8_t strip1 = 0xff;
  uint8_t strip2 = 0xff;
  uint8_t dir = tiltDir();

  // Note - this could probably be DRY'ed up with a lookup table, but
  // for now we're going to be very explicit and verbose
  switch(dir) {
  case TILTDIR_N:
    strip1 = stripOrder[7];
    strip2 = stripOrder[0];
    break;
  case TILTDIR_NE:
    strip1 = stripOrder[0];
    strip2 = stripOrder[1];
    break;
  case TILTDIR_E:
    strip1 = stripOrder[1];
    strip2 = stripOrder[2];
    break;
  case TILTDIR_SE:
    strip1 = stripOrder[2];
    strip2 = stripOrder[3];
    break;
  case TILTDIR_S:
    strip1 = stripOrder[3];
    strip2 = stripOrder[4];
    break;
  case TILTDIR_SW:
    strip1 = stripOrder[4];
    strip2 = stripOrder[5];
    break;
  case TILTDIR_W:
    strip1 = stripOrder[5];
    strip2 = stripOrder[6];
    break;
  case TILTDIR_NW:
    strip1 = stripOrder[6];
    strip2 = stripOrder[7];
    break;
  }

  // Send drops down the chosen strips
  if(strip1 != 0xff) {
    drops->startDrop(strip1);
  }
  if(strip2 != 0xff) {
    drops->startDrop(strip2);
  }
}

// Returns the direction of tilt, or TILTDIR_NONE if no tilt
uint8_t Tilts::tiltDir()
{
  uint8_t val = PIND;

  // Note - this could probably be DRY'ed up with a lookup table, but
  // for now we're going to be very explicit and verbose
  if(val & TILTS_FRONT) {
    if(val & TILTS_RIGHT) {
      return TILTDIR_NE;
    }
    else if(val & TILTS_LEFT) {
      return TILTDIR_NW;
    }
    else {
      return TILTDIR_N;
    }
  }
  else if(val & TILTS_BACK) {
    if(val & TILTS_RIGHT) {
      return TILTDIR_SE;
    }
    else if(val & TILTS_LEFT) {
      return TILTDIR_SW;
    }
    else {
      return TILTDIR_S;
    }
  }
  else if(val & TILTS_RIGHT) {
    return TILTDIR_E;
  }
  else if(val & TILTS_LEFT) {
    return TILTDIR_W;
  }
  else {
    return TILTDIR_NONE;
  }
}

