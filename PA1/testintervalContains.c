/*
 * Filename: testintervalContains.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/11/2019
 * Sources of Help: writeup
 */ 

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for intervalContains.s
 *
 * int intervalContains( int start, int end, int value );
 *
 * Checks to see if the interval contains the value (inclusive on both ends).
 *
 * Returns -1 if start > end
 * Returns 1 if the interval contains the value
 * Returns 0 otherwise.
 */
void testintervalContains() {

  /* Test interval containing the value */
  TEST( intervalContains( 0, 2, 1 ) == 1 );

  /* Test interval containing the value */
  TEST( intervalContains( 0, 1, 0 ) == 1 );

  /* Test invalid interval */
  TEST( intervalContains( 1, 0, 1 ) == -1 );

  /* Test outside of interval */
  TEST( intervalContains( 0, 1, 2 ) == 0 );

}


int main( void ) {

  fprintf( stderr, "Running tests for intervalContains...\n" );
  testintervalContains();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
