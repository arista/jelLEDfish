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
 * JelLEDfish - Rand.cpp
 * ----------------------------------------
 *
 * Pseudo-random generator, using an Xorshift RNG.  Attempts to seed
 * itself from the analog inputs, in the hopes that the "floating"
 * inputs are producing random noise.
 **/
#include "Rand.h"

Rand::Rand():
  next(seed())
{
}

// Generates a pseudo-random 32-bit number
uint32_t Rand::generate()
{
  uint32_t ret;
  ret = next;

  // Use an Xorshift pseudo RNG, similar (I think) to what Java now
  // uses - http://www.jstatsoft.org/v08/i14/paper
  next ^= next << 7;
  next ^= ((int32_t) next) >> 17;
  next ^= next << 21;

  return ret;
}

// Generates a pseudo-random 32-bit number >= low and < high
uint32_t Rand::generateRange(uint32_t low, uint32_t high)
{
  uint32_t ret;

  ret = low + (generate() % (high - low));

  return ret;
}

// Generates a seed used once when the generator is constructed
uint32_t Rand::seed()
{
  // Try using the analog inputs to generate a random seed - they're
  // not connected to anything, so maybe they'll return some kind of
  // random-ish value
  uint32_t ret = (analogRead(0) << 20) | (analogRead(1) << 10) | (analogRead(2));
  if(ret == 0) {
    // Random-ish seed
    ret = 305502;
  }
  return ret;
}
