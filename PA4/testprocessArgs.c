/*
 * Filename: testprocessArgs.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/26/2019
 * Sources of help: Partially given
 */

#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <getopt.h>

#include "pa4.h"
#include "test.h"

/*
 * Unit Test for processArgs.c
 *
 * int processArgs( argInfo_t * info, int argc, char * argv[] );
 *
 * Processes arguments passed into the executable.
 *
 * Returns
 *  - ARG_PARSING_ERROR on error parsing flags,
 *  - REGEX_ERROR if compiling the regular expression fails,
 *  - otherwise returns 0.
 */

void testprocessArgs() {
  argInfo_t info;
  
  // -e flag
  memset( &info, 0, sizeof(argInfo_t) );
  int argc = 3;
  char * argv[] = { "prog", "-e", "abc*" };
  optind = 0;

  TEST( processArgs( &info, argc, argv ) == 0 );
  TEST( info.flags == 0 );
  TEST( optind == 3 );

  // Multiple files
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 5;
  char * argv1[] = { "prog", "-e", "abc*", "file0", "file1" };
  optind = 0;

  TEST( processArgs( &info, argc, argv1 ) == 0 );
  TEST( info.flags == ARG_MULTI_FILE );
  TEST( optind == 3 );

  // Invalid flag
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 2;
  char * argv2[] = { "prog", "-f" };
  optind = 0;
  TEST( processArgs( &info, argc, argv2 ) == ARG_PARSING_ERROR );

  // Missing pattern
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 2;
  char * argv3[] = { "prog", "-e" };
  optind = 0;

  TEST( processArgs( &info, argc, argv3 ) == ARG_PARSING_ERROR );

  // regex error
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 3;
  char * argv4[] = { "prog", "-e", "jyft[" };
  optind = 0;

  TEST( processArgs( &info, argc, argv4 ) == REGEX_ERROR );
  TEST( info.flags == 0 );

  // Multiple flags
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 4;
  char * argv5[] = { "prog", "-n", "-v", "abc*" };
  optind = 0;

  TEST( processArgs( &info, argc, argv5 ) == 0 );
  TEST( info.flags == (ARG_N_FLAG | ARG_V_FLAG) );
  TEST( optind == 4 );

  // Test --regexp flag with file
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 4;
  char * argv6[] = { "prog", "file", "--regexp", "a" };
  optind = 0;

  TEST( processArgs( &info, argc, argv6 ) == 0 );
  TEST( info.flags == 0 );
  TEST( optind == 3 );
  
  // Test -e with no pattern
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 4;
  char * argv7[] = { "prog", "--regexp" };
  optind = 0;

  TEST( processArgs( &info, argc, argv7 ) == ARG_PARSING_ERROR );
  
  // all non help flags
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 7;
  char * argv8[] = { "prog", "-i", "-v", "-c", "-n", "-e", "a" };
  optind = 0;

  TEST( processArgs( &info, argc, argv8 ) == 0 );
  TEST( info.flags == (ARG_I_FLAG | ARG_V_FLAG | ARG_C_FLAG | ARG_N_FLAG) );
  TEST( optind == 7 );

  // Test --regexp flag without file
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 3;
  char * argv9[] = { "prog", "--regexp", "a" };
  optind = 0;

  TEST( processArgs( &info, argc, argv9 ) == 0 );
  TEST( info.flags == 0 );
  TEST( optind == 3 );
  
}

int main( void ) {
  
  fprintf( stderr, "Running tests for processArgs.c...\n" );
  testprocessArgs();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
