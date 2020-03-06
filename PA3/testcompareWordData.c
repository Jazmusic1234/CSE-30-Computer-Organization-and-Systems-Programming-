/*
 * Filename: testcompareWordData.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/13/2019
 * Sources of help: writeup, tutorialspoint.com
 */

#include <stdio.h>
#include <string.h>

#include "pa3.h"
#include "test.h"

unsigned int computeHashC( const char * str );

/*
 * Unit Test for compareWordData.s
 *
 * int compareWordData( const void * w1, const void * w2 );
 *
 * Compare words and hashvalues of 2 void pointers
 *      if wordData_t that w1 points to has smaller hashValue than wordData_t
 *          that w2 points to, OR hashValues are same but strncmp returns < 0,
 *          return -1
 *      if wordData_t that w1 points to has larger hashValue than wordData_t
 *          that w2 points to, OR hashValues are same but strncmp returns > 0,
 *          return 1
 *      if hashValues are same and strncmp returns 0, return 0
 */
void testcompareWordData() {

  unsigned int hash = computeHashC("hello");
  wordData_t w1 = {  
    .hashValue = hash 
  };

  wordData_t w2 = {  
    .hashValue = hash 
  };

  strncpy(w1.word, "hello", MAX_WORD_SIZE);
  strncpy(w2.word, "hello", MAX_WORD_SIZE);
  // Test "hello" and "hello"
  TEST( compareWordData(&w1, &w2) == 0 );

  w2.hashValue = computeHashC("Elephant");
  strncpy(w2.word, "Elephant", MAX_WORD_SIZE);
  // Test "hello" and "Elephant"
  TEST( compareWordData(&w1, &w2) == -1 );

  w1.hashValue = computeHashC("Elephant");
  w2.hashValue = hash;
  strncpy(w1.word, "Elephant", MAX_WORD_SIZE);
  strncpy(w2.word, "hello", MAX_WORD_SIZE);
  // Test "Elephant" and "hello"
  TEST( compareWordData(&w1, &w2) == 1 );

  // Test "a" and "z"
  w1.hashValue = 8;
  w2.hashValue = 8;
  strncpy(w1.word, "a", MAX_WORD_SIZE);
  strncpy(w2.word, "z", MAX_WORD_SIZE);
  TEST( compareWordData(&w1, &w2) == -1 );
 
  // Test "z" and "a"
  w1.hashValue = 8;
  w2.hashValue = 8;
  strncpy(w1.word, "z", MAX_WORD_SIZE);
  strncpy(w2.word, "a", MAX_WORD_SIZE);
  TEST( compareWordData(&w1, &w2) == 1 );
  
  // Test "z" and ""
  w1.hashValue = computeHashC("z");
  w2.hashValue = computeHashC("");
  strncpy(w1.word, "z", MAX_WORD_SIZE);
  strncpy(w2.word, "", MAX_WORD_SIZE);
  TEST( compareWordData(&w1, &w2) == 1 );

}

int main( void ) {

  fprintf( stderr, "Running tests for compareWordData...\n" );
  testcompareWordData();
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
