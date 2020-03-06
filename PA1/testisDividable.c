/*
 * Filename: testisDividable.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/16/2019
 * Sources of Help: testintervalContains.c, writeup
 */

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for isDividable.s
 *
 * int isDividable( int dividend, int divisor );
 *
 * Test if divisor divides evenly into the dividend
 * 
 * Returns -1 if divisor = 0
 * Returns 1 if dividable
 * Returns 0 is not dividable
 */
void testisDividable() {

  /* Test divisor = 0 */
  TEST( isDividable( 15, 0 ) == -1 );

  /* Test evenly divided */
  TEST( isDividable( 15, 3 ) == 1 );

  /* Test not evenly divided */
  TEST( isDividable( 15, 2 ) == 0 );

}


int main( void ) {
  
  fprintf( stderr, "Running tests for isDividable...\n" );
  testisDividable();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
