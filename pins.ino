/* pins.ino - contains functions pertaining to pins and the such
 * 
 * Created on: Jan 10, 2021
 * Author: thompsonc
 */

#include "pins.h"

// Write the state to the given pins. Pins are in binary pin format
void pins_write(byte pins, boolean state)
{
  PORTB = (state ? PORTB | pins : PORTB & ~pins);
}

// Set the data direction of the given pins. Pins are in the binary pin format
void pins_setMode(byte pins, boolean state)
{
  DDRB = (state ? DDRB | pins : DDRB & ~pins);
}

// Read data from the given pins. Pins are in the binary pin format
boolean pins_read(byte pins)
{
  return PINB & pins;
}
