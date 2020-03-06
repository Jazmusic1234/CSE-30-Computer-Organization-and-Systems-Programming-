/*
 * Filename: testmyRem.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/16/2019
 * Sources of help: testintervalContains.c, writeup
 */

 #include <stdio.h>

 #include "pa1.h"
 #include "test.h"

/*
 * Unit Test for myRem.s
 * 
 * int myRem( int dividend, int divisor );
 *
 * Calculate the remainder when dividend is divided by divisor
 *
 * Returns remainder
 */
void testmyRem() {
  
  /* Test divide evenly */
  TEST( myRem( 30, 5 ) == 0 );

  /* Test not divide evenly */
  TEST( myRem( 34, 9 ) == 7 );

  /* Test + dividend and + divisor */
  TEST( myRem( 12, 5 ) == (12 % 5) );

  /* Test + dividend and - divisor */
  TEST( myRem( 12, -5 ) == (12 % -5) );
  
  /* Test - dividend and + divisor */
  TEST( myRem( -12, 5 ) == (-12 % 5) );

  /* Test - dividend and i divisor */
  TEST( myRem( -12, -5 ) == (-12 % -5) );

}

int main( void ) {

  fprintf( stderr, "Running tests for myRem...\n" );
  testmyRem();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
 }

