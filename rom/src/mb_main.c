/* mb_main.c - contains main function, which initializes everything and performs the main loop
 * 
 * Created on: May 4, 2021
 * Author: Charles Thompson
 */

#include <mb_main.h>

int main(void)
{
  // Initialize everything...
  // Indicate we are initializing
  mb_pins_setModePA(PORTA_O_STATLED, output);
  mb_pins_writePA(PORTA_O_STATLED, low);

  // Initialize UART
  mb_uart_init();

  // Wait approximately 100ms for all other ICs to initialize
  // Use TCNT1 as it's 16 bits as opposed to TCNT0 which is 8 bit
  TCCR1A = INIT_TCCR1A; // Set all the counter registers
  TCCR1B = INIT_TCCR1B;
  TCCR1C = INIT_TCCR1C;
  TCNT1 = 0; // Reset delay

  while((uint16_t)TCNT1 < INIT_DELAY); // Wait 100ms

  // Write "Hello, World!" to UART
  while(!mb_uart_cts());
  mb_uart_writeData("Hello, World!", strlen("Hello, World!"));

  // Indicate we are done initializing
  mb_pins_writePA(PORTA_O_STATLED, high);

  // Loop until we can't loop no more...
  while(1)
  {

  }
  return 0;
}
