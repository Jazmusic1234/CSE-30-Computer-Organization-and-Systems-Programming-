/*
 * Filename: testlineShouldBePrinted.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/27/2019
 * Sources of help: Partially given
 */

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <getopt.h>

#include "pa4.h"
#include "test.h"

/*
 * Unit Test for lineShouldBePrinted.c
 *
 * int lineShouldBePrinted( const char * line, const argInfo_t * info );
 *
 * Checks if line should be printed in search().
 *
 * Returns
 *  - 1 if line should be printed
 *  - otherwise returns 0.
 */

void testlineShouldBePrinted() {
  argInfo_t info = { {0} };
  const char * line;
  char * pattern;
  int cflags = REG_EXTENDED | REG_NOSUB | REG_ICASE;

  // Test should print
  memset( &info, 0, sizeof(argInfo_t) );
  info.flags = ARG_N_FLAG;
  line = "hello";
  pattern = "hello";
  regcomp(&(info.pattern), pattern, cflags);
  TEST( lineShouldBePrinted(line, &info) == 1 );

  // Test should not print
  memset( &info, 0, sizeof(argInfo_t) );
  info.flags = ARG_N_FLAG;
  line = "party";
  pattern = "hello";
  regcomp(&(info.pattern), pattern, cflags);
  TEST( lineShouldBePrinted(line, &info) == 0 );


  // Test no -v flag
  memset( &info, 0, sizeof(argInfo_t) );
  info.flags = ARG_N_FLAG;
  line = "hello";
  pattern = "hello";
  regcomp(&(info.pattern), pattern, cflags);
  TEST( lineShouldBePrinted(line, &info) == 1 );

  // Test -v flag
  memset( &info, 0, sizeof(argInfo_t) );
  info.flags = ARG_N_FLAG | ARG_V_FLAG;
  line = "hello";
  pattern = "hello";
  regcomp(&(info.pattern), pattern, cflags);
  TEST( lineShouldBePrinted(line, &info) == 0 );
}

int main( void ) {
  
  fprintf( stderr, "Running tests for lineShouldBePrinted.c...\n" );
  testlineShouldBePrinted();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
