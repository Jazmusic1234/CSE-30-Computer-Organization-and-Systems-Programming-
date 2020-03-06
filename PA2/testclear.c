/*
 * Filename: testclear.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/29/2019
 * Sources of help: testscrollHorizontal.c
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for clear.s
 *
 * void clear( unsigned int pattern[], unsigned int part0, unsigned int part1 );
 *
 * Turns off specified bits in pattern with bit patterns part0 and part1
 *    If part0 or part1 bit value is 1, then bit in pattern becomes 0
 *    If part0 or part1 bit value is 0, then bit in pattern stays same
 */
void testclear() {
  unsigned int pattern[PATTERN_LEN] = { 0 };

  // Test writeup example
  pattern[0] = 0xFF00FF00;
  pattern[1] = 0xAAAAAAAA;

  clear( pattern, 0xFF000000, 0x88888888 );

  TEST( pattern[0] == 0x0000FF00 );
  TEST( pattern[1] == 0x22222222 );

  // Test clear first half
  pattern[0] = 0xFF00FF00;
  pattern[1] = 0xAAAAAAAA;

  clear( pattern, 0xFFFF0000, 0xFFFF0000 );

  TEST( pattern[0] == 0x0000FF00 );
  TEST( pattern[1] == 0x0000AAAA );

  // Test clear second half
  pattern[0] = 0xFF00FF00;
  pattern[1] = 0xAAAAAAAA;

  clear( pattern, 0x0000FFFF, 0x0000FFFF );

  TEST( pattern[0] == 0xFF000000 );
  TEST( pattern[1] == 0xAAAA0000 );

  // Test clear all
  pattern[0] = 0xFF00FF00;
  pattern[1] = 0xAAAAAAAA;

  clear( pattern, 0xFFFFFFFF, 0xFFFFFFFF );

  TEST( pattern[0] == 0x00000000 );
  TEST( pattern[1] == 0x00000000 );

}

int main( void ) {

  fprintf( stderr, "Running tests for clear...\n" );
  testclear();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
