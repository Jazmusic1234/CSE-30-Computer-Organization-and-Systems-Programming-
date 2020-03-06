/*
 * Filename: testcharacter.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/27/2019
 * Sources of help: testscrollHorizontal.c, writeup
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for character.s
 *
 * int character( unsigned int pattern[], char ch, 
 *    const char * alphabetPatterns[], const char * digitPatterns[] );
 *
 * Fills pattern with bit pattern of ch
 *    If letter, look up pattern in alphabetPatterns and return 0
 *    If number, look up pattern in digitPatterns and return 0
 *    If neither, return -1
 */
void testcharacter() {
  unsigned int pattern[PATTERN_LEN] = { 0 };

  const char * alphabetPatterns[] = ALPHABET_PATTERNS;
  const char * digitPatterns[] = DIGIT_PATTERNS;

  // Test uppercase letter
  pattern[0] = 0x00100001;
  pattern[1] = 0x1F00F001;

  TEST( character( pattern, 'A', alphabetPatterns, digitPatterns ) == 0);
  
  TEST( pattern[0] == 0x007E4242);
  TEST( pattern[1] == 0x7E424200);

  // Test lowercase letter
  pattern[0] = 0x00100001;
  pattern[1] = 0x1F00F001;

  TEST( character( pattern, 'a', alphabetPatterns, digitPatterns ) == 0 );

  TEST( pattern[0] == 0x007E4242 );
  TEST( pattern[1] == 0x7E424200 );

  // Test number
  pattern[0] = 0x00100001;
  pattern[1] = 0x1F00F001;

  TEST( character( pattern, '6', alphabetPatterns, digitPatterns ) == 0 );

  TEST( pattern[0] == 0x003C407C );
  TEST( pattern[1] == 0x42423C00 ); 

  // Test 9
  pattern[0] = 0x00100001;
  pattern[1] = 0x1F00F001;

  TEST( character( pattern, '9', alphabetPatterns, digitPatterns ) == 0 );

  TEST( pattern[0] == 0x003C4242 );
  TEST( pattern[1] == 0x3E023C00 ); 

  // Test neither letter or number
  pattern[0] = 0x00100001;
  pattern[1] = 0x1F00F001;

  TEST( character( pattern, '?', alphabetPatterns, digitPatterns ) == -1 );

}

int main( void ) {

  fprintf( stderr, "Running tests for character...\n" );
  testcharacter();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
