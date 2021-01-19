/* common.h - 
 * 
 * Created on: Jan 10, 2021
 * Author: thompsonc
 */

#ifndef COMMON_H_
#define COMMON_H_

// Define Arduino keywords for Eclipse
#ifndef PORTB
#include <stdint.h>
#include <string.h>

typedef uint8_t byte;
typedef byte boolean;

#define LOW 0
#define HIGH 1
#define INPUT LOW
#define OUTPUT HIGH

#define PCINT0_vect

#define ISR(intr) void isr()

void delay(int ms);

byte PORTB;
byte PINB;
byte DDRB;
byte TCCR0A;
byte TCCR0B;
byte TCNT0;
byte GIMSK;
byte PCMSK;
byte SREG;

#endif

#endif /* COMMON_H_ */
