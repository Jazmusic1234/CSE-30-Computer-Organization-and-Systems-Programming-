/*
 * Filename: testprintPattern.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/6/2019
 * Sources of help: tetscrollHorizontal.c, writeup
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for printPattern.s
 *
 * void printPattern( unsigned int pattern[], char on, char off );
 *
 * Prints out pattern as 8x8 grid 
 *    If bit is 1, print on 
 *    If bit is 0, print off 
 */
void testprintPattern() {
  unsigned int pattern[PATTERN_LEN] = { 0 };

  // Test writeup example
  pattern[0] = 0x00010203;
  pattern[1] = 0x04050607;

  printPattern( pattern, DEFAULT_ON_CHAR, DEFAULT_OFF_CHAR );

  // Test all 0
  pattern[0] = 0x00000000;
  pattern[1] = 0x00000000;

  printPattern( pattern, DEFAULT_ON_CHAR, DEFAULT_OFF_CHAR );

  // Test all 1
  pattern[0] = 0xFFFFFFFF;
  pattern[1] = 0xFFFFFFFF;

  printPattern( pattern, DEFAULT_ON_CHAR, DEFAULT_OFF_CHAR );

  // Test alternating
  pattern[0] = 0xAAAAAAAA;
  pattern[1] = 0xAAAAAAAA;

  printPattern( pattern, DEFAULT_ON_CHAR, DEFAULT_OFF_CHAR );

}

int main( void ) {

  fprintf( stderr, "Running tests for printPattern...\n" );
  testprintPattern();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
