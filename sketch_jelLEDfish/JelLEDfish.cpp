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
 * JelLEDfish - JelLEDfish.cpp
 * ----------------------------------------
 *
 * The JelLEDfish costume consists of 8 LED strips (tentacles), each
 * with 30 individually-addressable LED's (WS2812b chips) and 4 tilt
 * switches.  Normally the jellyfish is in "rainbow" mode, where it
 * slowly cycles all of its LED's through various colors.
 * Occasionally, a single white "drop" will "fall" down one of the
 * tentacles, and less frequently, a "ring" of 8 white "drops" will
 * fall.
 *
 * The 4 tilt switches will cause an entire "strip" of white dots to
 * fall down 2 of the tentacles depending on which way the costume is
 * tilted.
 *
 * The 8 LED strips are expected to be driven separately, with their
 * data input lines connected to PB0-5/PD6-7 (i.e., arduino digital
 * pins 6-13).  The tilt switches are expected to be normally-closed
 * switches hooked up to PD2-5 (i.e., arduino digital pins 2-5).  Use
 * constants.h to indicate which tilt switch and "tentacle" ended up
 * in which pin.
 **/
#include "LedStrip8.h"
#include "JelLEDfish.h"

JelLEDfish::JelLEDfish()
{
  rainbow.setLedStrip(&ledStrip);
  rainbow.setBrightness(RAINBOW_BRIGHTNESS);
  drops.setLedStrip(&ledStrip);
  singleDrops.setDrops(&drops);
  singleDrops.setRand(&rand);
  rings.setDrops(&drops);
  rings.setRand(&rand);
  tilts.setDrops(&drops);
}

void JelLEDfish::setup()
{
  // Each of the 8 LED strips is hooked up to a separate digital
  // output - outputs PB0-5 and PD6-7.  So we set up DDRB and DDRD to
  // configure those outputs.  At the same time, the 4 tilt switches
  // are hooked up to inputs PD2-5 and require pullup resistors, so we
  // setup PORTD appropriately.

  DDRB = B00111111;
  PORTB = B00000000;
  DDRD = B11000000;
  PORTD = B00111100;
}

void JelLEDfish::loop()
{
  uint64_t nowTime = time.runTimeMillis();

  // Render the LED's to be shown
  rainbow.render();
  drops.render();

  // Show the state of the LED's
  ledStrip.show();

  // Poll all the elements
  rainbow.poll(nowTime);
  drops.poll(nowTime);
  singleDrops.poll(nowTime);
  rings.poll(nowTime);
  tilts.poll();
}
