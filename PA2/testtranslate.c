/*
 * Filename: testtranslate.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/4/2019
 * Sources of help: tetscrollHorizontal.c, writeup
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for translate.s
 *
 * void translate( unsigned int pattern[], int hOffset, int vOffset );
 *
 * Translate pattern horizontally by hOffset and vertically by vOffset
 */
void testtranslate() {
  unsigned int pattern[PATTERN_LEN] = { 0 };

  // Test translate 0: should not move
  pattern[0] = 0x11111111;
  pattern[1] = 0x11111111;

  translate( pattern, 0, 0);

  TEST( pattern[0] == 0x11111111 );
  TEST( pattern[1] == 0x11111111 );

  // Test translate 2 right and 3 up
  pattern[0] = 0x11111111;
  pattern[1] = 0x11111111;

  translate( pattern , 2, -3);

  TEST( pattern[0] == 0x44444444 );
  TEST( pattern[1] == 0x44444444 );

}

int main( void ) {

  fprintf( stderr, "Running tests for translate...\n" );
  testtranslate();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
