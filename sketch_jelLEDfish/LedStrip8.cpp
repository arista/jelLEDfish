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
 * JelLEDfish - LedStrip8.cpp
 * ----------------------------------------
 *
 * Manages the display of the 240 LED's - 30/strip, 8 strips.  Each
 * strip is controlled by an individual digital output (PB0-5, PD6-7),
 * so that allows us to transmit independent data streams to multiple
 * strips at once.
 *
 * Our approach is to buffer up the state of all 240 LED's, then
 * transmit the entire "frame buffer" into the LED's all at once.  The
 * required signals are described in
 * https://www.adafruit.com/datasheets/WS2812B.pdf, but the basic idea
 * is that we transmit 24 bits of color data (in order of g, r, b, MSB
 * first) for the LED at the top, then for the one under that,
 * etc. for all 30 LED's.  Each bit takes 20 clock cycles (assuming a
 * 16MHz clock, or 62.5ns/cycle) - hold it high for 7 cycles, then
 * transmit the data (hi or low) for 6 cycles, then hold it low for 7
 * cycles.  The entire cycle also requires a full reset held low for
 * 50us.  When we are transmitting the data, we actually set the
 * entire PORTB and PORTD registers, thereby transmitting independent
 * data streams to all 8 strips simultaneously.  The entire process
 * should take 50us + (62.5ns * 20 * 24 * 30), or just under 1ms.
 *
 * To be able to meet the strict timing characteristics, we store all
 * of the PORTB and PORTD values that we will be feeding into the
 * process.  So, for example, portBData[3][0] holds the MSB green
 * value for LED #3 on strips 0-5 (bit0 strip 0, bit 1 strip 1, etc.)
 * while portBData[3][7] holds the LSB green value, portBData[3][8]
 * holds the MSB red value, portBData[3][16] holds the MSB blue value,
 * etc.  Likewise, portDData holds the values for strips 6-7 (bit 6
 * strip 6, bit7 strip 7).
 **/
#include "LedStrip8.h"

LedStrip8::LedStrip8()
{
  clear();
}

// Clears all the LED's
void LedStrip8::clear()
{
  uint8_t *portBDatap = &(portBData[0][0]);
  uint8_t *portDDatap = &(portDData[0][0]);
  uint16_t count = 30 * 24;

  for(; count > 0; count--) {
    // We clear out portB, but for portD we keep on the bits for the
    // pullup resistors for the tilt switch inputs
    (*portBDatap++) = B00000000;
    (*portDDatap++) = B00111100;
  }
}

// Sets the LED on the given strip (0-7) with the given LED number
// (0-29) to the given color.  Note that the color order is green
// (bits 16-23), red (bits 8-15), blue (bits 0-7)
void LedStrip8::setLed(uint8_t stripNum, uint8_t ledNum, uint32_t grb)
{
  uint8_t *ptr;
  uint8_t onMask;
  uint8_t offMask;
  uint8_t count;

  // Strips 0-5 go to PORTB, 6-7 go to PORTD
  if(stripNum < 6) {
    ptr = &(portBData[ledNum][23]);
    onMask = 1 << stripNum;
  }
  else {
    ptr = &(portDData[ledNum][23]);
    onMask = 1 << stripNum;
  }
  offMask = ~onMask;

  // Set the bits
  for(count = 0; count < 24; count++) {
    if(grb & 0x01) {
      (*ptr--) |= onMask;
    }
    else {
      (*ptr--) &= offMask;
    }
    grb >>= 1;
  }
}

// Returns the color value for the given rgb triple
uint32_t LedStrip8::toColor(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
  return
    (adjustBrightness(g, brightness) << 16) |
    (adjustBrightness(r, brightness) << 8) |
    (adjustBrightness(b, brightness));
}

// Adjusts the given color value by the given brightness (0-255)
uint32_t LedStrip8::adjustBrightness(uint8_t value, uint8_t brightness)
{
  return ((((uint32_t) value) * ((uint32_t) brightness)) >> 8) & 0xff;
}

// Write all the buffered data to the LED strips
void LedStrip8::show()
{
  uint8_t *dataBPtr = &(portBData[0][0]);
  uint8_t hiB = B00111111;
  uint8_t loB = B00000000;
  uint8_t dataB = *dataBPtr++;

  // Remember that even when we're setting PORTD to low, we still want
  // to hold the pullup resistors high for the tilt switches
  uint8_t *dataDPtr = &(portDData[0][0]);
  uint8_t hiD = B11111100;
  uint8_t loD = B00111100;
  uint8_t dataD = *dataDPtr++;

  uint16_t bitCount = 30 * 24;
  uint16_t resetCount = 250;

  cli();
  // Comments indicate # of clock cycles
  asm volatile(
               "out %[portB], %[loB]\n" // 1
               "out %[portD], %[loD]\n" // 1
               "resetLoop:\n"
               "sbiw %[resetCount], 1\n" // 2 - resetCount -= 1
               "brne resetLoop\n" // 1/2 - if(resetCount != 0) goto resetLoop

               "loopStart:\n"
               // Hold HI for 7 clock cycles (comments indicate # of clock cycles)
               "out %[portB], %[hiB]\n" // 1
               "out %[portD], %[hiD]\n" // 1
               "nop\n" // 1
               "nop\n" // 1
               "nop\n" // 1
               "nop\n" // 1
               "nop\n" // 1

               // Hold data value for 6 clock cycles, using that time
               // to load the next data values
               "out %[portB], %[dataB]\n" // 1
               "out %[portD], %[dataD]\n" // 1
               "ld %[dataB], %a[dataBPtr]+\n" // 2 - dataB = *dataBPtr++
               "ld %[dataD], %a[dataDPtr]+\n" // 2 - dataB = *dataBPtr++

               // Hold LO for 7 clock cycles
               "out %[portB], %[loB]\n" // 1
               "out %[portD], %[loD]\n" // 1
               "nop\n" // 1
               "sbiw %[bitCount], 1\n" // 2 - bitCount -= 1
               "brne loopStart\n" // 1/2 - if(bitCount != 0) goto loopStart

               :
               [bitCount] "+w" (bitCount),
               [resetCount] "+w" (resetCount),
               [dataB] "+r" (dataB),
               [dataD] "+r" (dataD)
               :
               [portB] "I" (_SFR_IO_ADDR(PORTB)),
               [hiB] "r" (hiB),
               [loB] "r" (loB),
               [dataBPtr] "e" (dataBPtr),
               [portD] "I" (_SFR_IO_ADDR(PORTD)),
               [hiD] "r" (hiD),
               [loD] "r" (loD),
               [dataDPtr] "e" (dataDPtr)
               );
  sei();
}
