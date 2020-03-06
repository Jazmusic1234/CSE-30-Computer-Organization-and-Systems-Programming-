/*
 * Filename: testtoggle.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/29/2019
 * Sources of help: tetscrollHorizontal.c, writeup
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for toggle.s
 *
 * void toggle( unsigned int pattern[], unsigned int part0, unsigned int part1 );
 *
 * Toggles specified bits in pattern with bit patterns part0 and part1
 *    If part0 or part1 bit value is 1, then bit in pattern inverts
 *    If part0 or part1 bit value is 0, then bit in pattern stays same
 */
void testtoggle() {
  unsigned int pattern[PATTERN_LEN] = { 0 };

  // Test writeup example
  pattern[0] = 0xCAFEBABE;
  pattern[1] = 0xDECAFBAD;

  toggle( pattern, 0x420C5E30, 0xDEADBEEF );

  TEST( pattern[0] == 0x88F2E48E );
  TEST( pattern[1] == 0x00674542 );

  // Test toggle first half
  pattern[0] = 0x88888888;
  pattern[1] = 0x88888888;

  toggle( pattern, 0xFFFF0000, 0xFFFF0000 );

  TEST( pattern[0] == 0x77778888 );
  TEST( pattern[1] == 0x77778888 );

  // Test toggle second half
  pattern[0] = 0x88888888;
  pattern[1] = 0x88888888;

  toggle( pattern, 0x0000FFFF, 0x0000FFFF );

  TEST( pattern[0] == 0x88887777 );
  TEST( pattern[1] == 0x88887777 );

  // Test toggle first half
  pattern[0] = 0x88888888;
  pattern[1] = 0x88888888;

  toggle( pattern, 0xFFFFFFFF, 0xFFFFFFFF );

  TEST( pattern[0] == 0x77777777 );
  TEST( pattern[1] == 0x77777777 );

}

int main( void ) {

  fprintf( stderr, "Running tests for toggle...\n" );
  testtoggle();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
