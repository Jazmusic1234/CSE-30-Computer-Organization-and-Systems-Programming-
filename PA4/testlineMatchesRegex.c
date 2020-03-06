/*
 * Filename: testlineMatchesRegex.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/26/2019
 * Sources of help: testprocessArgs.c
 */

#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <getopt.h>

#include "pa4.h"
#include "test.h"

/*
 * Unit Test for lineMatchesRegex.c
 *
 * int lineMatchesRegex( const regex_t * pattern, const char * line );
 *
 * Checks if a line matches regex pattern using regexec(pattern, line, 0, 0, 0)
 *
 * Returns
 *  - 1 if line matches regex pattern,
 *  - otherwise returns 0.
 */

void testlineMatchesRegex() {
  regex_t pattern;

  char * p;
  int cflags = REG_EXTENDED | REG_NOSUB | REG_ICASE;
  
  // Test match
  p = "hello";
  regcomp(&pattern, p, cflags);
  TEST( lineMatchesRegex(&pattern, "hello") == 1 );

  // Test sentence match
  p = "hello";
  regcomp(&pattern, p, cflags);
  TEST( lineMatchesRegex(&pattern, "hello world lol") == 1 );

  // Test does not match
  regcomp(&pattern, p, cflags);
  TEST( lineMatchesRegex(&pattern, "party") == 0 );

}

int main( void ) {
  
  fprintf( stderr, "Running tests for lineMatchesRegex.c...\n" );
  testlineMatchesRegex();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
