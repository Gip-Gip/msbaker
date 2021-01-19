/* pins.h - 
 * 
 * Created on: Jan 10, 2021
 * Author: thompsonc
 */

#ifndef PINS_H_
#define PINS_H_

#include "common.h"

#define PIN(pin) (1 << pin) // Converts decimal pin format to binary pin format

void pins_write(byte pins, boolean state);
void pins_setMode(byte pins, boolean state);
boolean pins_read(byte pins);

#endif /* PINS_H_ */
