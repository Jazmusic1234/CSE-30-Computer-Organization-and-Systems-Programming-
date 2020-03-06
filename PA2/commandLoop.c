/*
 * Filename: commandLoop.c
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/7/2019
 * Sources of help: writeup, Week 5 Discussion Worksheet, Week 3 Discussion
 *    Worksheet
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "pa2.h"
#include "pa2Strings.h"
#include <errno.h>

/*
 * Function Name: commandLoop.c
 * Function Prototype: void commandLoop( char on, char off );
 * Description: Allows user to manipulate bits in pattern
 * Parameters: on - on char
 *             off - off char
 *
 * Side Effects: Print to stdout
 * Error conditions: None
 * Return Value: None
 */
void commandLoop( char on, char off ) {

  char buffer[BUFSIZ];

  unsigned int pattern[PATTERN_LEN] = { 0 };

  const char * commands[] = COMMANDS;
  const char * alpha[] = ALPHABET_PATTERNS;
  const char * digit[] = DIGIT_PATTERNS;
  char * arg1;
  char * arg2;
  char * endPtr1;
  char * endPtr2;
  unsigned int first;
  unsigned int second;

  // Prompt user for string
  if(shouldPrompt() == 1) {
    printf(STR_COMMAND_USAGE);
  }

  // Loop as long as user doesn't input Ctrl + D
  for( PRINT_PROMPT; fgets(buffer, BUFSIZ, stdin) != NULL; PRINT_PROMPT ) {
    
    // Replace newline character with NUL character
    char * newline = strchr(buffer, '\n');
    if(newline != NULL) {
      *newline = '\0';
    }
  
    // If command is empty, reprompt
    char * command = strtok(buffer, DELIM); 
    if(command == NULL) {
      continue;
    }

    // Parse args based on command entered
    int commandIndex = findCommand(command, commands);
    switch (commandIndex) {
      case HELP:
        printf(STR_COMMAND_USAGE);
        continue;

      case SET:
      case CLEAR:
      case TOGGLE:
        // Get args
        arg1 = strtok(NULL, DELIM);
        arg2 = strtok(NULL, DELIM);
        if(arg1 == NULL || arg2 == NULL) {    // Missing args
          printf(STR_ERR_COMMAND_MISSING_ARG);
        } else if(strtok(NULL, DELIM) != NULL) {    // Extra args
          printf(STR_ERR_EXTRA_ARG);
        } else {
          errno = 0;
          first = strtoul(arg1, &endPtr1, PATTERN_BASE);
          second = strtoul(arg2, &endPtr2, PATTERN_BASE);

          // Check for number conversion errors
          if(errno != 0 || *endPtr1 != '\0' || *endPtr2 != '\0') {
            printf(STR_ERR_PATTERN_INVALID);
          } else {
            if(commandIndex == SET) {
              set(pattern, first, second);         
            } else if(commandIndex == CLEAR) {
              clear(pattern, first, second);
            } else if(commandIndex == TOGGLE) {
              toggle(pattern, first, second);
            }
            printPattern(pattern, on, off);
          }
        }
        continue;

      case INVERT:
        if(strtok(NULL, DELIM) != NULL) {   // Extra args
          printf(STR_ERR_EXTRA_ARG);
        } else {
          invert(pattern);
          printPattern(pattern, on, off);
        }
        continue;

      case CHARACTER:
        arg1 = strtok(NULL, DELIM);
        if(arg1 == NULL) {    // Missing args
          printf(STR_ERR_COMMAND_MISSING_ARG); 
        } else if(strtok(NULL, DELIM) != NULL) {    // Extra args
          printf(STR_ERR_EXTRA_ARG);
        } else if(strlen(arg1) > 1) {   // If not a single char
          printf(STR_ERR_CHAR_COMMAND_SINGLE);
        } else {
          int valid = character(pattern, *arg1, alpha, digit);
          if(valid == -1) {   // If character is not letter or number
            printf(STR_ERR_CHAR_INVALID);
          } else {
            printPattern(pattern, on, off);
          }
        }
        continue;

      case SAY:
        arg1 = strtok(NULL, DELIM);
        if(arg1 == NULL) {    // Missing args
          printf(STR_ERR_COMMAND_MISSING_ARG); 
        } else if(strtok(NULL, DELIM) != NULL) {    // Extra args
          printf(STR_ERR_EXTRA_ARG);
        } else {
          say(arg1, on, off);
        }
        continue;

      case SCROLL_HORIZONTAL:
      case SCROLL_VERTICAL:
        arg1 = strtok(NULL, DELIM);
        if(arg1 == NULL) {    // Missing args
          printf(STR_ERR_COMMAND_MISSING_ARG); 
        } else if(strtok(NULL, DELIM) != NULL) {    // Extra args
          printf(STR_ERR_EXTRA_ARG);
        } else {
          errno = 0;
          first = strtol(arg1, &endPtr1, OFFSET_BASE );

          // Check for number conversion errors
          if(errno != 0 || *endPtr1 != '\0') {
            printf(STR_ERR_INT_INVALID);
          } else {
            if(commandIndex == SCROLL_HORIZONTAL) {
              scrollHorizontal(pattern, first); 
            } else if(commandIndex == SCROLL_VERTICAL) {
              scrollVertical(pattern, first);
            }
            printPattern(pattern, on, off);
          }
        }
        continue;

      case TRANSLATE:
        arg1 = strtok(NULL, DELIM);
        arg2 = strtok(NULL, DELIM);
        if(arg1 == NULL || arg2 == NULL) {    // Missing args
          printf(STR_ERR_COMMAND_MISSING_ARG);
        } else if(strtok(NULL, DELIM) != NULL) {    // Extra args
          printf(STR_ERR_EXTRA_ARG);
        } else {
          errno = 0;
          first = strtol(arg1, &endPtr1, OFFSET_BASE);
          second = strtol(arg2, &endPtr2, OFFSET_BASE);

          // Check for number conversion errors
          if(errno != 0 || *endPtr1 != '\0' || *endPtr2 != '\0') {
            printf(STR_ERR_INT_INVALID); 
          } else {
            translate(pattern, first, second);
            printPattern(pattern, on, off);
          }
        }
        continue;

      default:
        printf(STR_ERR_BAD_COMMAND);
        continue;

    }
    
  }

  printf(STR_END_PROMPT); 

}
