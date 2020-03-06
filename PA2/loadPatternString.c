/*
 * Filename: loadPatternString.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 4/25/2019
 * Sources of Help: writeup, piazza post #496
 */

#include "pa2.h"

/*
 * Function Name: loadPattenString()
 * Function Prototype: void loadPatternString( unsigned int pattern[], 
 *      const char * patternStr );
 * Description: Goes through each character in patternStr and sets bits in
 *      pattern to on or off based on patternStr
 * Parameters: pattern - array of bits that represents the 8x8 image
 *             patternStr - 64 character long char that determines pattern
 *                  @ is on, - is off
 *
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 */

void loadPatternString( unsigned int pattern[], const char * patternStr ) {
  pattern[0] = 0x00000000;
  pattern[1] = 0x00000000;
  
  int bitValue = 0;

  for(int i = 0; i < PATTERN_STR_LEN/DIVIDE_HALF; i++) {
    if(patternStr[i] == DEFAULT_ON_CHAR) {
      bitValue = 1;
    } else if(patternStr[i] == DEFAULT_OFF_CHAR) {
      bitValue = 0;
    }
    pattern[0] = (pattern[0] << 1) | bitValue;
  }
  for(int j = PATTERN_STR_LEN/DIVIDE_HALF; j < PATTERN_STR_LEN; j++) {
    if(patternStr[j] == DEFAULT_ON_CHAR) {
      bitValue = 1;
    } else if(patternStr[j] == DEFAULT_OFF_CHAR) {
      bitValue = 0;
    }
    pattern[1] = (pattern[1] << 1) | bitValue;
  }


}

