/*
 * Filename: findCommand.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 4/25/2019
 * Sources of Help: writeup
 */

#include <stdio.h>
#include <string.h>
#include "pa3.h"

/*
 * Function Name: findCommand()
 * Function Prototype: int findCommand( const char * cmdString, 
 *      const char * commands[] );
 * Description: Look for given cmdString in commands and return its index
 * Parameters: cmdString - command to find
 *             commands - array of commands to search through
 *
 * Side Effects: None
 * Error Conditions: if cmdString is null, return -1
 *                   if commands is null, return -1
 *                   if cmdString not found, return -1
 * Return Value: if error, return -1
 *               else, return index
 */

int findCommand( const char * cmdString, const char * commands[] ) {

  
  // If cmdString = NULL, error
  if( cmdString == NULL ) {
    return -1;
  }
  
  // If commands = NULL, error
  if( commands == NULL ) {
    return -1;
  }

 // If cmdString not in commands, error
  // Else return index
  // Get length of commands
  int length = 0;
  while(commands[length] != NULL) {
    length = length + 1;
  }
  for(int i = 0; i < length; i++) {
    if(strncmp(cmdString, commands[i], BUFSIZ) == 0) {
      return i;   
    }
  }
  return -1;

}

