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
 * JelLEDfish - Time.cpp
 * ----------------------------------------
 *
 * Keeps track of the time since restart.  It uses Timer1 (16-bit)
 * running as fast as it can, with an interrupt handler to capture the
 * overflow and increment a 64-bit value.  For a 16MHz clock, that
 * counter should increment every 4.096ms (although, for some reason,
 * it seems to be incrementing at twice that rate - perhaps the timer
 * naturally runs at twice the clock speed?  I suppose I should read
 * the data sheet).
 *
 * The resulting 64-bit value should be able to keep time for
 * thousands of years.
 **/
#include "Time.h"

// Global pointer to a Time, so that the interrupt handler can get to
// it
Time *Time::globalTime;

Time::Time():
  counter(0)
{
  // Set the global time that will be called by the interrupt handler
  globalTime = this;
  
  // Disable interrupts
  cli();

  // Note - writing TCNT1L also atomically stores TCNT1H, so it's
  // important to do the writes in this order
  TCNT1H = 0;
  TCNT1L = 0;

  // Set "Normal Mode", that is, the counter simply runs to max
  // (0xFFFF) then starts again at 0
  TCCR1A = 0x0;
  // Set the clock to no prescaling
  TCCR1B = 0x1;
  // Enable the overflow interrupt
  TIMSK1 = 0x1;

  // Enable interrupts
  sei();
}

// Called by the interrupt handler whenever the timer overflows
void Time::increment()
{
  counter++;
}

// Interrupt vector for when the counter overflows.  All it does is
// increment the counter.
ISR(TIMER1_OVF_vect)
{
  Time::globalTime->increment();
}

// Returns the number of milliseconds the Time class has been running
// has been running
uint64_t Time::runTimeMillis()
{
  // 488 = 32MHz / 65536.0 = overflows/second.  Not sure why it's
  // 32MHz instead of 16MHz
  return (counter * 1000) / 488;
}
