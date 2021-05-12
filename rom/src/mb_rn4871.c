/* mb_rn4871.c - Contains all functions needed to interface with the RN4871
 * 
 * Created on: May 11, 2021
 * Author: thompsonc
 */

#include <mb_rn4871.h>

/* mb_rn4871_init - initializes the RN4871
 *
 */
void mb_rn4871_init()
{
  // Enter command mode
  mb_rn4871_sendCmd(RN4871_ENTRCMD);

  // Check to see what the flags are set to...
  mb_rn4871_sendCmd(RN4871_SETFLG);

  // Set name of bluetooth device
  mb_rn4871_sendCmd(RN4871_SETNAME);

  mb_rn4871_sendCmd(RN4871_REBOOT); // Reboot the RN4871
}

/* mb_rn4871_sendCmd - sends a command to the rn4871, retry if error is received
 *
 * uint8_t *cmd - command to send
 */
void mb_rn4871_sendCmd(uint8_t *cmd)
{
  for(bool aok = false; aok != true;)
  {
    mb_uart_writeData(cmd, strlen((char*)cmd));
    if(mb_rn4871_waitForReady()) aok = true;
  }
}

/* mb_rn4871_waitForReady - waits for a response from the RN4871
 *
 * returns true if there are no errors, false otherwise
 */
bool mb_rn4871_waitForReady()
{
  mb_uart_readData(dataBuffer, sizeof(dataBuffer));
  return !mb_rn4871_compareResponse(dataBuffer, RN4871_ERR);
}

/* mb_rn4871_seekToNoWhitespace - seeks to next point in a string where there is no whitespace
 *
 * returns pointer to the point where no whitespace is found in the string
 *
 * uint8_t *str - string being seeked through
 */
uint8_t *mb_rn4871_seekToNoWhitespace(uint8_t *str)
{
  while(isspace((char)*str) && *str) str++; // Continue incrementing the pointer until no longer whitespace
  return str;
}

/* mb_rn4871_seekToWhitespace - seeks to next point in a string where there is whitespace
 *
 * returns pointer to the point where whitespace is found in the string
 *
 * uint8_t *str - string being seeked through
 */
uint8_t *mb_rn4871_seekToWhitespace(uint8_t *str)
{
  while(!isspace((char)*str) && *str) str++; // Continue incrementing the pointer until whitespace is found
  return str;
}

/* mb_rn4871_compareResponse - removes whitespace and truncates a given buffer to the length of a comparison string, and performs a strncmp
 *
 * returns true if strings are equal, false otherwise
 *
 * uint8_t *buffer - buffer with string to be compared
 *
 * uint8_t *comparison - string to be compared to; buffer is effectively truncated to the length of this string when comparing
 */
bool mb_rn4871_compareResponse(uint8_t *buffer, uint8_t *comparison)
{
  buffer = mb_rn4871_seekToNoWhitespace(buffer); // Remove preceeding whitespace

  // Compare the two strings, if they are not equal (strncmp returns non-zero), return false
  if(strncmp((char *)buffer, (char *)comparison, strlen((char *)comparison))) return false;

  // Otherwise, they are equal and return true!
  return true;
}

/* mb_rn4871_skipResponse - skip a response in a given buffer by seeking past whitespace, and then seeking past non-whitespace
 *
 * uint8_t *buffer - string being seeked through
 */
uint8_t *mb_rn4871_skipResponse(uint8_t *buffer)
{
  buffer = mb_rn4871_seekToNoWhitespace(buffer);
  buffer = mb_rn4871_seekToWhitespace(buffer);
  return buffer;
}
