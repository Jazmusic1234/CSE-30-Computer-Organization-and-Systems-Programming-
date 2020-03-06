/*
 * Filename: .c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 6/1/2019
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
 * Unit Test for .c
 *
 * 
 *
 * 
 *
 * Returns
 *  - 
 *  - 
 */

void test() {
  argInfo_t info = { {0} };
  const char * line;

  // Test should print
  memset( &info, 0, sizeof(argInfo_t) );
  info.flags = ARG_N_FLAG;
  line = "hello";
  pattern = "hello";
  regcomp(&(info.pattern), pattern, cflags);
  TEST( lineShouldBePrinted(line, &info) == 1 );

}

int main( void ) {
  
  fprintf( stderr, "Running tests for .c...\n" );
  test();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
