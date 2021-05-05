/* mb_pins.c - Contains functions required to interact with pins in a fast manner
 * 
 * Created on: May 4, 2021
 * Author: Charles Thompson
 */

#include <mb_pins.h>

/* mb_pins_setModePA - set pins on port A to the given mode
 *
 * mb_binPins pins - pins in binary pin format
 *
 * mb_pinMode mode - mode to set pins to, either input or output
 */
void mb_pins_setModePA(mb_binPins pins, mb_pinMode mode)
{
  // If we wish to set the pins to input, we need to set the pins' corresponding bits to zero
  if(mode == input)
  {
    DDRA &= ~pins;
  }

  // Otherwise, we are setting the mode to output, and we simply need to set the pin's corresponding bits to one
  else
  {
    DDRA |= pins;
  }
}

/* mb_pins_setModePB - set pins on port B to the given mode
 *
 * mb_binPins pins - pins in binary pin format
 *
 * mb_pinMode mode - mode to set pins to, either input or output
 */
void mb_pins_setModePB(mb_binPins pins, mb_pinMode mode)
{
  // If we wish to set the pins to input, we need to set the pins' corresponding bits to zero
  if(mode == input)
  {
    DDRB &= ~pins;
  }

  // Otherwise, we are setting the mode to output, and we simply need to set the pin's corresponding bits to one
  else
  {
    DDRB |= pins;
  }
}

/* mb_pins_writePA - write to the given pins on port A with the given state
 *
 * mb_binPins pins - pins in binary pin format
 *
 * mb_pinState state - state to set pins to, either high or low
 */
void mb_pins_writePA(mb_binPins pins, mb_pinState state)
{
  // If we wish to set the pins to low, we need to set the pins' corresponding bits to zero
  if(state == low)
  {
    PORTA &= ~pins;
  }

  // Otherwise, we are setting the mode to output, and we simply need to set the pin's corresponding bits to one
  else
  {
    PORTA |= pins;
  }
}

/* mb_pins_writePB - write to the given pins on port B with the given state
 *
 * mb_binPins pins - pins in binary pin format
 *
 * mb_pinState state - state to set pins to, either high or low
 */
void mb_pins_writePB(mb_binPins pins, mb_pinState state)
{
  // If we wish to set the pins to low, we need to set the pins' corresponding bits to zero
  if(state == low)
  {
    PORTB &= ~pins;
  }

  // Otherwise, we are setting the mode to output, and we simply need to set the pin's corresponding bits to one
  else
  {
    PORTB |= pins;
  }
}

/* mb_pins_readPA - returns OR'd state of given pins on port A
 *
 * mb_binPins pins - pins to read
 */
mb_pinState mb_pins_readPA(mb_binPins pins)
{
  if(PINA & pins) return high;
  return low;
}

/* mb_pins_readPB - returns OR'd state of given pins on port B
 *
 * mb_binPins pins - pins to read
 */
mb_pinState mb_pins_readPB(mb_binPins pins)
{
  if(PINB & pins) return high;
  return low;
}
