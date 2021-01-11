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
}

void loop()
{
  pins_write(LED, HIGH);
  delay(1000);
  pins_write(LED, LOW);
  delay(1000);
}
