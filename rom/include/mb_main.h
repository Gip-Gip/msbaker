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

#define INIT_TCCR1A 0b00000000 // TCCR0A value while doing the initialization delay
#define INIT_TCCR1B 0b00000101 // TCCR0B value while doing the initialization delay
#define INIT_TCCR1C 0b00000000
#define INIT_DELAY (uint16_t)1953

#endif /* INCLUDE_MB_MAIN_H_ */
