/* mb_uart.c - Contains functions required to send and receive data over UART
 * 
 * Created on: May 4, 2021
 * Author: Charles Thompson
 */

#include <mb_uart.h>

/* mb_uartInit - initialize UART
 *
 */
void mb_uart_init()
{
  // Set the TX and RTS pins to output
  mb_pins_setModePA(PORTA_O_UARTTX | PORTA_O_UARTRTS, output);
  // Set the RX and CTS pins to input
  mb_pins_setModePA(PORTA_I_UARTRX | PORTA_I_UARTCTS, input);

  // Deassert TX and RTS to signify no data is being transmitted and that the microcontroller is not ready for data
  mb_pins_writePA(PORTA_O_UARTTX | PORTA_O_UARTRTS, high);
}

/* mb_uart_cts - returns true if it's clear to transmit data over uart
 *
 */
bool mb_uart_cts()
{
  return !mb_pins_readPA(PORTA_I_UARTCTS);
}

/* mb_uart_writeData - transmit data over UART
 *
 * uint8_t *data - pointer to data
 *
 * size_t length - length of data
 */
void mb_uart_writeData(uint8_t *data, size_t length)
{
  TCCR0A = UART_TCCR0A; // Set the timer control registers
  TCCR0B = UART_TCCR0B;

  TCNT0 = UART_DELAY; // Set TCNT0 to UART_DELAY so we skip the next delay...
  // Go through all the bytes in data
  for(size_t i = 0; i < length; i++)
  {
    while(TCNT0 < UART_DELAY); // if the loop has already iterated, wait for the last byte to finish transmitting
                                        // Otherwise this delay will be ignored...

    TCNT0 = 0; // Reset delay
    mb_pins_writePA(PORTA_O_UARTTX, low); // Assert TX, starting byte

    for(uint8_t j = 1; j; j <<= 1) // Go through all the bits in the current byte of data
    {
      while(TCNT0 < UART_DELAY); // wait for the previous bit to finish transmitting
      TCNT0 = 0; // Reset delay
      mb_pins_writePA(PORTA_O_UARTTX, j & data[i]); // right the current bit of the current byte. 0 = low, anything else = high
    }

    while(TCNT0 < UART_DELAY); // Wait for the previous bit to finish transmitting
    TCNT0 = 0; // Reset delay
    mb_pins_writePA(PORTA_O_UARTTX, high); // Deassert TX pin, ending byte
  }
}

/* mb_uart_writeData - transmit data over UART, with flow control
 *
 * uint8_t *data - pointer to data
 *
 * size_t length - length of data
 */
void mb_uart_writeDataCts(uint8_t *data, size_t length)
{
  while(!mb_uart_cts());
  mb_uart_writeData(data, length);
}

/* mb_uart_readData - reads data from RX and writes it to a pointer, not going past a specified length
 *
 * returns 0 if data transmission is smaller than length, -1 otherwise
 *
 * uint8_t *data - the pointer to be written to
 *
 * size_t length - the maximum length of data to read
 */
int mb_uart_readData(uint8_t *data, size_t length)
{
  TCCR0A = UART_TCCR0A; // Set the timer control registers
  TCCR0B = UART_TCCR0B;

  mb_pins_writePA(PORTA_O_UARTRTS, low); // Assert RTS so the rn4871 knows we're ready to receive data

  while(mb_pins_readPA(PORTA_I_UARTRX) == high); // wait for RX to be pulled low

  TCNT0 = UART_DELAY / 2; // Offset the timer by 1/2 a bit transmission to help guarantee we read the stable part of the bit

  for(int i = 0; i < length; i ++)
  {
    data[i] = 0; // Clear the byte being written to
    while(TCNT0 < UART_DELAY);

    TCNT0 = 0; // Skip the byte-start bit

    // End Of Transmission logic: If RX is still high, we are done receiving data!
    if(mb_pins_readPA(PORTA_I_UARTRX) == high)
    {
      mb_pins_writePA(PORTA_O_UARTRTS, high); // Deassert RTS so the rn4871 knows we're NOT ready to receive data
      return 0;
    }

    for(uint8_t j = 1; j; j <<= 1)
    {
      while(TCNT0 < UART_DELAY); // Wait for the transmission of the last bit to end

      TCNT0 = 0; // Reset the timer

      if(mb_pins_readPA(PORTA_I_UARTRX) == high) data[i] |= j; // If the RX pin is high, set the current bit to a one
    }

    while(TCNT0 < UART_DELAY); // Finish the last bit

    TCNT0 = 0; // Reset the timer

    while(mb_pins_readPA(PORTA_I_UARTRX) == high && TCNT0 < UART_DELAY * 2); // Wait for the last bit to be transmitted

    TCNT0 = UART_DELAY * 0.75; // Offset the timer by 1/4 a bit transmission to help guarantee we read the stable part of the bit
  }

  mb_pins_writePA(PORTA_O_UARTRTS, high); // Deassert RTS so the rn4871 knows we're NOT ready to receive data
  return -1; // Return -1 to indicate we read past the length specified!
}
