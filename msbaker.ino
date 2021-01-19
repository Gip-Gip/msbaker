/* msbaker.ino - Contains functions called by the arduino kernel
 * 
 * Created on: Jan 8, 2021
 * Author: thompsonc
 */

#include "msbaker.h"

#define LED PIN(1)

void setup()
{
  pins_setMode(LED, OUTPUT);
  pins_write(LED, HIGH);
  uart_init();
}

void loop()
{
  byte in[16];

  while(pins_read(UART_RX)) TCNT0 = 0;
  uart_read();

  while(uart_newData())
  {
    uart_copyString(in, '\0', sizeof(in));
    uart_writeString(in, sizeof(in));
  }
}
