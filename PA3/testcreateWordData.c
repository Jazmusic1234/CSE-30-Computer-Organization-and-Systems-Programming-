/*
 * Filename: testcreateWordData.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/14/2019
 * Sources of help: writeup
 */

#include <stdio.h>
#include <string.h>

#include "pa3.h"
#include "test.h"

unsigned int computeHashC( const char * str );

/*
 * Unit Test for createWordData.c
 *
 * void createWordData( wordData_t * wordData, const char * wordStr,
 *        unsigned int decade, unsigned int count );
 *
 * Fill fields of wordData struct to represent wordStr
 */
void testcreateWordData() {

  wordData_t w = {
    .hashValue = 0
  };

  unsigned int index = 9;

  // Test "hello", 1890, 30
  createWordData( &w, "hello", 1890, 30 );
  TEST( strncmp( w.word, "hello", MAX_WORD_SIZE ) == 0);
  TEST( w.counts[index] == 30 );
  TEST( w.hashValue == computeHash("hello") );
  TEST( w.counts[0] == 0 );
}

int main( void ) {

  fprintf( stderr, "Running tests for createWordData...\n" );
  testcreateWordData();
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
