/*
 * Filename: testsay.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/7/2019
 * Sources of help: tetscrollHorizontal.c, writeup
 */

#include <stdio.h>

#include "pa2.h"
#include "pa2Strings.h"
#include "test.h"

/*
 * Unit Test for say.s
 *
 * void say( const char * str, char on, char off );
 *
 * Prints out each character in str
 *    If character is not valid, print error
 *    Else, look up character in look up table
 */
void testsay() {

  // Test "a"
  say( "a", DEFAULT_ON_CHAR, DEFAULT_OFF_CHAR );

  // Test "CSE30"
  say( "CSE30", DEFAULT_ON_CHAR, DEFAULT_OFF_CHAR );

  // Test "pattern"
  say( "pattern", DEFAULT_ON_CHAR, DEFAULT_OFF_CHAR );

  // Test "who?@*"
  say( "who?@*", DEFAULT_ON_CHAR, DEFAULT_OFF_CHAR );

}

int main( void ) {

  fprintf( stderr, "Running tests for say...\n" );
  testsay();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
