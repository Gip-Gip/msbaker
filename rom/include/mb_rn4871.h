/* mb_rn4871.h - Includes and definitions for interfacing with the RN4871 chip
 * 
 * Created on: May 11, 2021
 * Author: thompsonc
 */

#ifndef INCLUDE_MB_RN4871_H_
#define INCLUDE_MB_RN4871_H_

#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <ctype.h>
#include <mb_pins.h>
#include <mb_uart.h>
#include <mb_main.h>

#define RN4871_ENTRCMD (uint8_t *)"$$$"
#define RN4871_EXITCMD (uint8_t *)"---\r"
#define RN4871_READY (uint8_t *)"CMD>"
#define RN4871_AOK (uint8_t *)"AOK"
#define RN4871_ERR (uint8_t *)"ERR"
#define RN4871_END (uint8_t *)"END"
#define RN4871_REBOOT (uint8_t *)"R,1\r"
#define RN4871_SETNAME (uint8_t *)"S-,MSBAKER\r"
#define RN4871_SETFLG (uint8_t *)("SR,8000\r")

void mb_rn4871_init();
bool mb_rn4871_waitForReady();
void mb_rn4871_sendCmd(uint8_t *cmd);
bool mb_rn4871_compareResponse(uint8_t *buffer, uint8_t *comparison);
uint8_t *mb_rn4871_seekToNoWhitespace(uint8_t *str);
uint8_t *mb_rn4871_seekToWhitespace(uint8_t *str);
uint8_t *mb_rn4871_skipResponse(uint8_t *buffer);

#endif /* INCLUDE_MB_RN4871_H_ */
