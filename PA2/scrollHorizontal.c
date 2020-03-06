/*
 * Filename: scrollHorizontal.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 4/25/2019
 * Sources of Help: writeup, Week 4 Discussion Worksheet
 */

#include <stdio.h>
#include "pa2.h"

int rotateRight( unsigned int byte, int offset );
int rotateLeft( unsigned int byte, int offset );

/*
 * Function Name: scrollHorizontal()
 * Function Prototype: void scrollHorizontal( unsigned int pattern[], 
 *      int offset );
 * Description: Scroll pattern horizontally by given offset
 * Parameters: pattern - array of bits that represents the 8x8 image
 *             offset - how much to scroll right or left by
 *
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 */

void scrollHorizontal( unsigned int pattern[], int offset ) {
 
  for(int j = 0; j < PATTERN_LEN; j++) {
    for(int i = 0; i < BYTE_BITWIDTH / DIVIDE_HALF; i++) { 
      // Create specific byte mask for specific byte
      unsigned int byteMask = MSB_MASK >> (i * BYTE_BITWIDTH);

      // Extract byte
      unsigned int byte = pattern[j] & byteMask;
      // Move byte to MSB position
      byte = byte >> (INT_BITWIDTH - (BYTE_BITWIDTH * (i + 1)));
      
      if(offset < 0) {
        byte = rotateLeft(byte, (offset * -1));
      } else if(offset > 0) { 
        byte = rotateRight(byte, offset);
      }

      // Move byte back to correct byte position
      byte = byte << (INT_BITWIDTH - (BYTE_BITWIDTH * (i + 1)));
      byte = byte & byteMask;
      
      // Combine byte with rest of pattern
      byte = byte | (pattern[j] & ~byteMask);
      pattern[j] = byte;
    }
  }

}

int rotateRight( unsigned int byte, int offset) {
  
  for(int i = 0; i < offset % BYTE_BITWIDTH; i++) {
    // Get right most bit
    unsigned int bit = byte & 1;

    // Move bit over to left most position in byte
    bit = bit << ( BYTE_BITWIDTH - 1 );

    // Shift byte 1 bit to the right then combine with extracted bit
    byte = (byte >> 1) | bit;

  }

  return byte;
}

int rotateLeft( unsigned int byte, int offset ) {

  for(int i = 0; i < offset % BYTE_BITWIDTH; i++) {
    // Get left most bit
    unsigned int bit = byte & 128;

    // Move bit over to right most position in byte
    bit = bit >> ( BYTE_BITWIDTH - 1 );

    // Shift byte 1 bit to the left then combine with extracted bit
    byte = (byte << 1) | bit;

  }
  
  return byte;
}
