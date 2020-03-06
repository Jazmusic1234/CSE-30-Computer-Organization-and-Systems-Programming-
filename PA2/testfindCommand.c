/*
 * Filename: test.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/1/2019
 * Sources of help: tetscrollHorizontal.c, writeup
 */

#include <stdio.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for findCommand.c
 *
 * int findCommand( const char * cmdString, const char * commands[] );
 *
 * Look for given cmdString in commands
 *    If cmdString is NULL, return -1
 *    If commands is NULL, return -1
 *    If cmdString is not in commands, return -1
 *    Otherwise, return index
 */
void testfindCommand() {
/*  const char * commands[3];
  
  // Test commands is NULL
  TEST( findCommand("a", commands) == -1 );

  // Test cmdString is NULL
  commands[0] = "a";
  commands[1] = "b";
  commands[2] = NULL;
  TEST( findCommand(NULL, commands) == -1 );
  
  // Test cmdString is not in commands
  commands[0] = "a";
  commands[1] = "s";
  commands[2] = NULL;
  TEST( findCommand("z", commands) == -1 );

  // Test command is found
  commands[0] = "a";
  commands[1] = "p";
  commands[2] = NULL;
  TEST( findCommand("p", commands) == 1 );
*/
  // Test given commands array
  const char * c[] = COMMANDS;
  TEST( findCommand("set", c) == 0 );
}

int main( void ) {

  fprintf( stderr, "Running tests for findCommand...\n" );
  testfindCommand();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
