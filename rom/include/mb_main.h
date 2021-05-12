/* mb_main.h - Includes and definitions for mb_main.c
 * 
 * Created on: May 4, 2021
 * Author: Charles Thompson
 */

#ifndef INCLUDE_MB_MAIN_H_
#define INCLUDE_MB_MAIN_H_

#include <avr/io.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <mb_pins.h>
#include <mb_uart.h>
#include <mb_rn4871.h>

/* Project-wide globals go here
 *
 * Every other file besides mb_main.c has EXTERN undefined. This allows us to make an extern reference to all the global variables
 * However, in mb_main.c, EXTERN is defined, and is empty, making the global variable defined in mb_main.c
 */
#ifndef EXTERN
#define EXTERN extern
#endif

EXTERN uint8_t dataBuffer[256];

#define INIT_TCCR1A 0b00000000 // TCCR1A value while doing the initialization delay
#define INIT_TCCR1B 0b00000101 // TCCR1B value while doing the initialization delay
#define INIT_TCCR1C 0b00000000 // TCCR1C value while doing the initialization delay
#define INIT_DELAY (uint16_t)1953 // TCNT delay of 100ms approx.

#endif /* INCLUDE_MB_MAIN_H_ */
