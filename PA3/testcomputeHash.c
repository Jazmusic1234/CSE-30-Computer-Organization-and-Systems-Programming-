/*
 * Filename: testcomputeHash.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/12/2019
 * Sources of help: writeup
 */

#include <stdio.h>

#include "pa3.h"
#include "test.h"

unsigned int computeHashC( const char * str );

/*
 * Unit Test for computeHash.s
 *
 * unsigned int computeHash( const char * str );
 *
 * Create and return hash value of given string
 *
 * Returns hash value of given string
 */
void testcomputeHash() {

  // Test "hello"
  TEST( computeHash("hello") == computeHashC("hello") );

  // Test "Elephant"
  TEST( computeHash("Elephant") == computeHashC("Elephant") );

  // Test "elephant"
  TEST( computeHash("elephant") == computeHashC("elephant") );

  // Test ""
  TEST( computeHash("") == computeHashC("") );

}

int main( void ) {

  fprintf( stderr, "Running tests for computeHash...\n" );
  testcomputeHash();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}

unsigned int computeHashC( const char * str ){
  unsigned int hash = HASH_START_VAL;
  for(int i = 0; str[i] != '\0'; i++) {
    hash = hash * HASH_PRIME + str[i];
  }
  return hash;
}
