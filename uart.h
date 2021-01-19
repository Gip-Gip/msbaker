/* uart.h - 
 * 
 * Created on: Jan 11, 2021
 * Author: thompsonc
 */

#ifndef UART_H_
#define UART_H_

#include "common.h"
#include "pins.h"

#define UART_TX PIN(3)
#define UART_RX PIN(4)
#define UART_DELAY 61

#define UART_TCCR0A 0b00000000
#define UART_TCCR0B 0b00000001
#define UART_GIMSK 0b00100000
#define UART_PCMSK UART_RX
#define UART_BUFFSIZE 256

#define UART_RN4871_READY "CMD> "
#define UART_RN4871_DONE "END\r"
#define UART_RN4871_ENTRCMD "$$$"
#define UART_RN4871_EXITCMD "---\r"
#define UART_RN4871_BTNAME "MSBAKER"
#define UART_RN4871_SBTNAME ("S-," UART_RN4871_BTNAME "\r")

void uart_init();
void uart_write(byte *data, int dataSize);
void uart_writeString(byte *string, int maxlen);
void uart_read();
boolean uart_newData();
byte uart_pop();
void uart_copy(byte *dest, int len);
void uart_copyString(byte *dest, byte delem, int len);
boolean uart_contains(byte *str);
void uart_clearBuffer();
void uart_rn4871_writeCmd(byte *str);
void uart_rn4871_enterCmdMode();
void uart_rn4871_exitCmdMode();

#endif /* UART_H_ */
