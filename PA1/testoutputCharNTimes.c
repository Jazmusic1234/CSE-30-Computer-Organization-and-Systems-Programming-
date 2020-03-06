/*
 * Filename: testoutputCharNTimes.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/16/2019
 * Sources of Help: testintervalContains.c, writeup, piazza post #152
 */

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for outputCharNTimes.s
 *
 * void outputCharNTimes( char ch , int n);
 *
 * Prints character ch to stdout n times
 */
void testoutputCharNTimes() {

  /* Test outputChar */
  outputCharNTimes( 'a', 5 );
  printf("\n");
  outputCharNTimes( '/', 5 );
  printf("\n");
  outputCharNTimes( '?', 5 );
  printf("\n");

}


int main( void ) {
  
  fprintf( stderr, "Running tests for outputCharNTimes...\n" );
  testoutputCharNTimes();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
