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
 * JelLEDfish - Rings.cpp
 * ----------------------------------------
 *
 * Randomly sends "rings" of drops down all 8 strips
 **/
#include "Rings.h"

Rings::Rings():
  nextTime(0)
{
}

// Sets the Drops
void Rings::setDrops(Drops *drops)
{
  this->drops = drops;
}

// Sets the Rand
void Rings::setRand(Rand *rand)
{
  this->rand = rand;
}

// See if it's time to send the next ring
void Rings::poll(uint64_t nowTime)
{
  if(nowTime >= nextTime) {
    next();
  }
}

// Send the next ring and determine the next time
void Rings::next()
{
  uint8_t stripNum;
  for(stripNum = 0; stripNum < 8; stripNum++) {
    drops->startDrop(stripNum);
  }
  nextTime += rand->generateRange(RINGS_LOW, RINGS_HIGH);
}
