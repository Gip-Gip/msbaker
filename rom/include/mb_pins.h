/* mb_pins.h - Includes and definitions for mb_pins.c
 * 
 * Created on: May 4, 2021
 * Author: Charles Thompson
 */

#ifndef INCLUDE_MB_PINS_H_
#define INCLUDE_MB_PINS_H_

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// Possible modes a pin can be in. input = 0, output = 1
typedef enum
{
    input,
    output
} mb_pinMode;

// Possible states a pin can be in. low = 0, high = 1
typedef enum
{
  low,
  high
} mb_pinState;

// Macro which converts pin number to binary pin format
#define PIN(pin) (1 << pin)

// type for specifying which pins to write to, using low-level binary pin format
typedef uint8_t mb_binPins;

/* FUNCTION DEFINITIONS
 *
 * basic function definitions so files other than mb_pins.c don't give the wrong types to functions defined in mb_pins.c
 * see mb_pins.c for better functions definitions...
 */

void mb_pins_setModePA(mb_binPins pins, mb_pinMode mode);
void mb_pins_setModePB(mb_binPins pins, mb_pinMode mode);
void mb_pins_writePA(mb_binPins pins, mb_pinState state);
void mb_pins_writePB(mb_binPins pins, mb_pinState state);
mb_pinState mb_pins_readPA(mb_binPins pins);
mb_pinState mb_pins_readPB(mb_binPins pins);

/* GLOBAL PIN DEFINITIONS
 *
 * pin naming conventions goes as follows
 *
 * [PORT]_[I/O/IO]_[FUNCTION]
 * for example, the status led would be
 * PORTA_O_STATLED
 *
 * PORTA since the status led pin is on port A
 * O since the pin is only written to
 * STATLED is an abbreviation of status led
 */

#define PORTA_O_UARTTX PIN(0) // UART TX pin
#define PORTA_I_UARTRX PIN(1) // UART RX pin
#define PORTA_I_UARTCTS PIN(2) // UART CTS pin
#define PORTA_O_UARTRTS PIN(3) // UART RTS pin
#define PORTA_O_STATLED PIN(4) // Status LED pin

#endif /* INCLUDE_MB_PINS_H_ */
