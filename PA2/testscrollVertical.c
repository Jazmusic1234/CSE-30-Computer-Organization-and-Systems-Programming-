/*
 * Filename: testscrollVertical.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/27/2019
 * Sources of help: testscrollHorizontal.c, writeup
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for scrollVertical.c
 *
 * void scrollVertical( unsigned int pattern[], const int offset );
 *
 * Scroll vertically by offset.
 *    If offset is positive, shift down.
 *    If offset is negative, shift up.
 */
void testscrollVertical() {
  unsigned int pattern[PATTERN_LEN] = { 0 };

  // Test offset = 0: shouldn't move
  pattern[0] = 0xAAAAAAAA;
  pattern[1] = 0xCCCCCCCC;

  scrollVertical( pattern, 0 );

  TEST( pattern[0] == 0xAAAAAAAA );
  TEST( pattern[1] == 0xCCCCCCCC );

  // Test offset = 4: should swap pattern[0] and pattern[1]
  pattern[0] = 0xABCDEF01;
  pattern[1] = 0xCFCFCFCF;

  scrollVertical( pattern, 4 );

  TEST( pattern[0] == 0xCFCFCFCF );
  TEST( pattern[1] == 0xABCDEF01 );

  // Test offset = 12: should act like offset of 4
  pattern[0] = 0xABCDEF01;
  pattern[1] = 0xCFCFCFCF;

  scrollVertical( pattern, 12 );

  TEST( pattern[0] == 0xCFCFCFCF );
  TEST( pattern[1] == 0xABCDEF01 );

  
  // Test offset = -4: should move left by 4
  pattern[0] = 0xABCDEF01;
  pattern[1] = 0xCFCFCFCF;

  scrollVertical( pattern, -4 );

  TEST( pattern[0] == 0xCFCFCFCF );
  TEST( pattern[1] == 0xABCDEF01 );
}

int main( void ) {

  fprintf( stderr, "Running tests for scrollVertical...\n" );
  testscrollVertical();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
