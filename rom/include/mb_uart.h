/* mb_uart.h - Includes and definitions for mb_uart.c
 * 
 * Created on: May 4, 2021
 * Author: thompsonc
 */

#ifndef INCLUDE_MB_UART_H_
#define INCLUDE_MB_UART_H_

#include <avr/io.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <mb_pins.h>

#define UART_TCCR0A 0b00000000 // value to set TCCR0A when doing UART operations
#define UART_TCCR0B 0b00000001 // value to set TCCR0B when doing UART operations
#define UART_DELAY (uint8_t)80 // Amount of clock cycles between bits read/sent through UART, assuming clock speed of 10MHZ and baud rate of 115200

/* FUNCTION DEFINITIONS
 *
 * basic function definitions so files other than mb_uart.c don't give the wrong types to functions defined in mb_uart.c
 * see mb_uart.c for better functions definitions...
 */

void mb_uart_init();
bool mb_uart_cts();
void mb_uart_writeData(uint8_t *data, size_t length);
void mb_uart_writeDataCts(uint8_t *data, size_t length);
int mb_uart_readData(uint8_t *data, size_t length);

#endif /* INCLUDE_MB_UART_H_ */
