/*
 * Filename: testmyURem.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/12/2019
 * Sources of help: writeup
 */

#include <stdio.h>

#include "pa3.h"
#include "test.h"

unsigned int remC(unsigned int dividend, unsigned int divisor);

/*
 * Unit Test for myURem.s
 *
 * unsigned int myURem( unsigned int dividend, unsigned int divisor );
 *
 * Calculates remainder when dividing dividend by divisor where dividend,
 *    divisor, and remainder are all unsigned integers
 *
 * Returns the remainder
 */
void testmyURem() {

  // Test 12%4
  TEST( myURem(12, 4) == remC(12, 4) );

  // Test -12%4
  TEST( myURem(-12, 4) == remC(-12, 4) );

  // Test 12%-4
  TEST( myURem(12, -4) == remC(12, -4) );

  // Test -12%-4
  TEST( myURem(-12, -4) == remC(-12, -4) );

  // Test 4000005%10
  TEST( myURem(4000005, 10) == remC(4000005, 10) );
}

int main( void ) {

  fprintf( stderr, "Running tests for myURem...\n" );
  testmyURem();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}

unsigned int remC( unsigned int dividend, unsigned int divisor ) {
  return (dividend % divisor);
}

