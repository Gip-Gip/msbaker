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

typedef uint8_t byte;
typedef byte boolean;

#define LOW 0
#define HIGH 1
#define INPUT LOW
#define OUTPUT HIGH

void delay(int ms);

byte PORTB;
byte PINB;
byte DDRB;
#endif

#endif /* COMMON_H_ */
