/*
 * Filename: testloadPatternString.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/27/2019
 * Sources of help: tetscrollHorizontal.c, writeup
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for loadPatternString.s
 *
 * void loadPatternString( unsigned int pattern[], const char * patternStr );
 *
 * Sets bits in pattern to either on or off depending on patternStr
 *    '@' is the on bit
 *    '-' is the off bit
 */
void testloadPatternString() {
  unsigned int pattern[PATTERN_LEN] = { 0 };

  // Test writeup example
  const char * patternStr = "@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-";
  pattern[0] = 0x00000000;
  pattern[1] = 0x00000000;

  loadPatternString( pattern, patternStr);

  TEST( pattern[0] == 0xAAAAAAAA );
  TEST( pattern[1] == 0xAAAAAAAA );

  // Test pattern not already 0
  pattern[0] = 0x11111111;
  pattern[1] = 0x11111111;

  loadPatternString( pattern, patternStr);

  TEST( pattern[0] == 0xAAAAAAAA );
  TEST( pattern[1] == 0xAAAAAAAA );

}

int main( void ) {

  fprintf( stderr, "Running tests for loadPatternString...\n" );
  testloadPatternString();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
