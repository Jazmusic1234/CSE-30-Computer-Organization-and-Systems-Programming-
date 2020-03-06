/*
 * Filename: testinvert.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/3/2019
 * Sources of help: tetscrollHorizontal.c, writeup
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for invert.s
 *
 * void invert( unsigned int pattern[] );
 *
 * Invert all the bits in pattern
 */
void testinvert() {
  unsigned int pattern[PATTERN_LEN] = { 0 };

  // Test writeup example
  pattern[0] = 0x1CEB00DA;
  pattern[1] = 0xDEADBEEF;

  invert( pattern );

  TEST( pattern[0] == 0xE314FF25 );
  TEST( pattern[1] == 0x21524110 );

}

int main( void ) {

  fprintf( stderr, "Running tests for invert...\n" );
  testinvert();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
