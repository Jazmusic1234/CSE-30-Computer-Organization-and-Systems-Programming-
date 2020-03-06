/*
 * Filename: testfindSlotIndex.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/12/2019
 * Sources of help: writeup
 */

#include <stdio.h>

#include "pa3.h"
#include "test.h"

unsigned int findSlotIndexC( const char * wordStr, size_t numSlots );

/*
 * Unit Test for findSlotIndex.s
 *
 * unsigned int findSlotIndex( const char * wordStr, size_t numSlots );
 *
 * Calculate index in slot array for given string
 *
 * Returns index of wordStr in slot array
 */
void testfindSlotIndex() {

  // Test "hello" and 6
  TEST( findSlotIndex("hello", 6) == findSlotIndexC("hello", 6) );

  // Test "Elephant" and 3
  TEST( findSlotIndex("Elephant", 3) == findSlotIndexC("Elephant", 3) );

  // Test "elephant" and 9
  TEST( findSlotIndex("elephant", 9) == findSlotIndexC("elephant", 9) );

  // Test "" and 5
  TEST( findSlotIndex("", 5) == findSlotIndexC("", 5) );

}

int main( void ) {

  fprintf( stderr, "Running tests for findSlotIndex...\n" );
  testfindSlotIndex();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}

unsigned int findSlotIndexC( const char * wordStr, size_t numSlots ){
  unsigned int hash = HASH_START_VAL;
  for(int i = 0; wordStr[i] != '\0'; i++) {
    hash = hash * HASH_PRIME + wordStr[i];
  }
  unsigned int index = hash % numSlots;
  return index;
}
