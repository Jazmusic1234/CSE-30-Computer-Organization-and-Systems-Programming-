/*
 * Filename: testset.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/27/2019
 * Sources of help: tetscrollHorizontal.c, writeup
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for set.s
 *
 * void set( unsigned int pattern[], unsigned int part0, unsigned int part1 );
 *
 * Turns on specified bits in pattern with bit patterns part0 and part1
 *    If part0 or part1 bit value is 1, then bit in pattern becomes 1
 *    If part0 or part1 bit value is 0, then bit in pattern stays same
 */
void testset() {
  unsigned int pattern[PATTERN_LEN] = { 0 };

  // Test writeup example
  pattern[0] = 0x00100001;
  pattern[1] = 0x1F00F001;

  set( pattern, 0x420C5E30, 0xF001F008 );

  TEST( pattern[0] == 0x421C5E31 );
  TEST( pattern[1] == 0xFF01F009 );

  // Test set first half
  pattern[0] = 0x00100001;
  pattern[1] = 0x1F00F001;

  set( pattern, 0xFFFF0000, 0xFFFF0000 );

  TEST( pattern[0] == 0xFFFF0001 );
  TEST( pattern[1] == 0xFFFFF001 );

  // Test set second half
  pattern[0] = 0x00100001;
  pattern[1] = 0x1F00F001;

  set( pattern, 0x0000FFFF, 0x0000FFFF );

  TEST( pattern[0] == 0x0010FFFF );
  TEST( pattern[1] == 0x1F00FFFF );

  // Test set all
  pattern[0] = 0x00100001;
  pattern[1] = 0x1F00F001;

  set( pattern, 0xFFFFFFFF, 0xFFFFFFFF );

  TEST( pattern[0] == 0xFFFFFFFF );
  TEST( pattern[1] == 0xFFFFFFFF );

}

int main( void ) {

  fprintf( stderr, "Running tests for set...\n" );
  testset();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
