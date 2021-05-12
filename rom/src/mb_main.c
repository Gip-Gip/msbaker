/* mb_main.c - contains main function, which initializes everything and performs the main loop
 * 
 * Created on: May 4, 2021
 * Author: Charles Thompson
 */

#define EXTERN // Define EXTERN here. See mb_main.h for more details

#include <mb_main.h>

void mb_main_waitOnICs()
{
  // Wait approximately 100ms for all other ICs to initialize
  // Use TCNT1 as it's 16 bits as opposed to TCNT0 which is 8 bit
  TCCR1A = INIT_TCCR1A; // Set all the counter registers
  TCCR1B = INIT_TCCR1B;
  TCCR1C = INIT_TCCR1C;
  TCNT1 = 0; // Reset delay
}

int main(void)
{
  // Initialize everything...
  // Indicate we are initializing
  //mb_pins_setModePA(PORTA_O_STATLED, output);
  //mb_pins_writePA(PORTA_O_STATLED, low);

  // Initialize UART
  mb_uart_init();

  // Wait on ICs to initialize
  mb_main_waitOnICs();

  // Initialize the RN4871
  mb_rn4871_init();

  // Wait on the RN4871 to finish rebooting
  mb_main_waitOnICs();

  // Indicate we are done initializing
  //mb_pins_writePA(PORTA_O_STATLED, high);

  // Loop until we can't loop no more...
  while(1)
  {
      mb_uart_readData(dataBuffer, sizeof(dataBuffer));
      mb_uart_writeDataCts(dataBuffer, strnlen((char*)dataBuffer, sizeof(dataBuffer)));
  }
  return 0;
}
