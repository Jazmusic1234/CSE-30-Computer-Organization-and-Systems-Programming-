/*
 * Filename: testoutputChar.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/16/2019
 * Sources of Help: testintervalContains.c, writeup, piazza post #152
 */

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for outputChar.s
 *
 * void outputChar( char ch );
 *
 * Prints character ch to stdout
 */
void testoutputChar() {

  /* Test outputChar */
  outputChar( 'a' );
  printf("\n");
  outputChar( '/' );
  printf("\n");
  outputChar( '?' );
  printf("\n");

}


int main( void ) {
  
  fprintf( stderr, "Running tests for outputChar...\n" );
  testoutputChar();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
