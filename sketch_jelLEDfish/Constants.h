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
 * JelLEDfish - Constants.h
 * ----------------------------------------
 **/
#ifndef CONSTANTS_H
#define CONSTANTS_H

// The interval (msec) for advancing the falling drops
#define DROPS_POLL_INTERVAL 40
// The brightness (0-255) for the rainbow
#define RAINBOW_BRIGHTNESS 50
// The brightness (0-255) of the drops
#define DROPS_BRIGHTNESS 100
// The interval (msec) for advancing the rainbow
#define RAINBOW_POLL_INTERVAL 25
// The interval range (msec) for sending down rings
#define RINGS_LOW 3000
#define RINGS_HIGH 60000
// The interval range (msec) for sending down individual drops
#define SINGLEDROPS_LOW 1000
#define SINGLEDROPS_HIGH 5000
// The PIND inputs assigned to the tilt switches
#define TILTS_FRONT 0x04
#define TILTS_BACK 0x08
#define TILTS_RIGHT 0x10
#define TILTS_LEFT 0x20

// Once the costume is assembled, the LED strips may be arranged in a
// different order from the order they're wired into the arduino
// (strips 0-5 = PB0-5, strips 6-7 = PD6-7), so we use this to
// indicate the order in which the strips actually ended up.  For
// example, the first element indicates which LED strip ended up in
// the NNE corner, then the ENE corner, etc.  The strips starts from
// the front right ("NNE") and go clockwise (looking down from the
// top).
#define STRIP_ORDER {3, 4, 1, 7, 2, 6, 5, 0}

#endif // CONSTANTS_H
