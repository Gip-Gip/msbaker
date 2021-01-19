/* uart.ino - contains functions required for software UART
 * 
 * Created on: Jan 11, 2021
 * Author: thompsonc
 */

#include "uart.h"

byte uart_buffer[UART_BUFFSIZE];
byte uart_biIndex, uart_boIndex;

// Initialize the UART interface with the RN4871
void uart_init()
{
  /* Interrupts are too slow for UART, at least at the clock speed of the ATTINY
  // Enable pin interrupts on the RX pin
  GIMSK = UART_GIMSK;
  PCMSK = UART_PCMSK;
  */

  // Set the TX pin to output and the RX pin to input
  pins_setMode(UART_TX, OUTPUT);
  pins_setMode(UART_RX, INPUT);

  // Set TX to high
  pins_write(UART_TX, HIGH);

  // Wait for the RN4871 to initialize, 100ms delay
  delay(100);
  // Set the buffer indexes to zero
  uart_biIndex = 0, uart_boIndex = 0;
  // Adjust the timer to better suit UART
  TCCR0A = UART_TCCR0A;
  TCCR0B = UART_TCCR0B;

  // Enter command mode
  uart_rn4871_enterCmdMode();

  // Set the BT name
  uart_rn4871_writeCmd((byte *)UART_RN4871_SBTNAME);

  pins_write(PIN(1), LOW);

  uart_rn4871_exitCmdMode();
}

// Write a given number of bytes to UART
void uart_write(byte *data, int dataLength)
{
  TCNT0 = 0;
  for(int i = 0; i < dataLength; i++)
  {
    while(TCNT0 < UART_DELAY);

    TCNT0 = 0;
    pins_write(UART_TX, LOW);

    for(byte j = 1; j; j <<= 1)
    {
      while(TCNT0 < UART_DELAY);
      TCNT0 = 0;
      pins_write(UART_TX, j & data[i]);
    }

    while(TCNT0 < UART_DELAY);
    TCNT0 = 0;
    pins_write(UART_TX, HIGH);
  }
}

// Write a null terminated string to UART
void uart_writeString(byte *string, int maxlen)
{
  uart_write(string, strnlen((char*)string, maxlen));
}

// Read data from UART into the buffer
void uart_read()
{
  bool reading = true;
  for(byte inByte = 0; reading; inByte = 0)
  {
    while(TCNT0 < (UART_DELAY / 2));
    TCNT0 = 0;

    for(byte i = 1; i; i <<= 1)
    {
      while(TCNT0 < UART_DELAY);
      TCNT0 = 0;
      if(pins_read(UART_RX)) inByte |= i;
    }

    // Yes, I expect the index to overflow. Not the best programming practice, but code efficiency tho...
    // Also, side note, this hard codes the buffer size of 256 into the code
    uart_buffer[uart_biIndex++] = inByte;

    // Wait for the last data byte to finish transmitting
    while(TCNT0 < UART_DELAY);
    TCNT0 = 0;
    // Wait for the RX line to be pulled low for the next bit, or for more than 1 stop bit to be transmitted
    while(pins_read(UART_RX) && TCNT0 < UART_DELAY);
    reading = TCNT0 < UART_DELAY;
    TCNT0 = 0;
  }
}

// Check to see if there is still unread data in the buffer
boolean uart_newData()
{
  return uart_biIndex != uart_boIndex;
}

// Read data from the buffer and mark that data as read
byte uart_pop()
{
  if(uart_newData()) return uart_buffer[uart_boIndex++];
  else return 0;
}

void uart_clearBuffer()
{
  uart_boIndex = uart_biIndex;
}

// Copy data from the buffer to another pointer
void uart_copy(byte *dest, int len)
{
  while(len--)
  {
    *dest++ = uart_pop();
  }
}

// Copy a string from the buffer to another pointer
void uart_copyString(byte *dest, byte delem, int len)
{
  for(int i = 0; i < len && dest[i - 1] != delem; i ++)
  {
    dest[i] = uart_pop();

    // Make the string null terminated
    if(i + 1 < len) dest[i + 1] = 0;
  }
}

boolean uart_contains(byte *str)
{
  byte boIndexOld = uart_boIndex;
  for(byte i = 0; uart_newData();)
  {
    if(str[i] == uart_pop()) i ++;
    else i = 0;
    // If we've reached the end of the string to be compared, it's been found!
    if(!str[i])
    {
      uart_boIndex = boIndexOld;
      return true;
    }
  }
  uart_boIndex = boIndexOld;
  return false;
}

// Returns the old buffer index if the response wants to be read by any other functions...
int uart_rn4871_waitForReady()
{
  byte inString[sizeof(UART_RN4871_READY)];
  int boIndexOld = uart_boIndex;

  // Wait for CMD> or END

  while(!uart_contains((byte *)UART_RN4871_READY) && !uart_contains((byte *)UART_RN4871_DONE))
  {
    while(pins_read(UART_RX)) TCNT0 = 0;
    uart_read();
  }

  return boIndexOld;
}

// Max command size of 16
// Returns the old buffer index if the response wants to be read by any other functions...
void uart_rn4871_writeCmd(byte *str)
{
  uart_writeString(str, strnlen((char *)str, 16));
  uart_rn4871_waitForReady();
}

void uart_rn4871_enterCmdMode()
{
  uart_rn4871_writeCmd((byte *)UART_RN4871_ENTRCMD);
  uart_clearBuffer();
}

void uart_rn4871_exitCmdMode()
{
  uart_rn4871_writeCmd((byte *)UART_RN4871_EXITCMD);
  uart_clearBuffer();
}
