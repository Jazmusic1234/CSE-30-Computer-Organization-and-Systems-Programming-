/*
 * Filename: interactiveLoop.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/18/2019
 * Sources of Help: writeup
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "pa3.h"
#include "pa3Strings.h"
#include <errno.h>

/*
 * Function Name: interactiveLoop()
 * Function Prototype: void interactiveLoop( const wordTable_t * table ); 
 * Description: Prints out list of possible commands and takes in command from
 *        user
 * Parameters: table - table to search for inputted word in
 *
 * Side Effects: Print error message to stdout if needed
 * Error Conditions: error when parsing argument
 *                   
 * Return Value: If error, print out corresponding error statement
 */
void interactiveLoop( const wordTable_t * table ) {

  char buffer[BUFSIZ];
  char NULL_CHAR = '\0';

  const char * commands[] = COMMANDS;

  char * arg;

  // Prompt user for string
  if(shouldPrompt() == 1) {
    printf(STR_HELP);
  }

  // Loop as long as user doesn't input Ctrl + D
  for(PRINT_PROMPT; fgets(buffer, BUFSIZ, stdin) != NULL; PRINT_PROMPT) {
    
    // Replace newline character with NUL character
    char * newline = strchr(buffer, NEWLINE_CHAR);
    if(newline != NULL) {
      *newline = NULL_CHAR;
    }

    // If command is empty, reprompt
    char * command = strtok(buffer, ""); 
    if(command == NULL) {
      continue;
    }

    // Parse args based on command entered
    int commandIndex = findCommand(command, commands);
    switch(commandIndex) {
      case HELP:
        printf(STR_ERR_BAD_COMMAND);
        continue;
      
      case DATA:
      case PLOT:
        arg = strtok(NULL, "");         
        if(arg == NULL) {    // Missing args
          printf(STR_ERR_COMMAND_MISSING_ARG);
        } else if(strtok(NULL, "") != NULL) {    // Extra args
          printf(STR_ERR_COMMAND_EXTRA_ARG);
        } else {
          wordData_t * w;
          createWordData(w, arg, 0, 0);
          unsigned int index = findSlotIndex(arg, table->numSlots);     
          wordData_t * wordData = bsearch(&w, 
            table->slotPtr[index].wordDataPtr, table->slotPtr[index].numWords,
            sizeof(struct wordData), compareWordData);

          // No data for this word
          if(wordData == NULL) {
            printf(STR_NO_DATA);
            continue;
          } else {    // Word found
            char plot[PLOT_ROWS][PLOT_COLS];
            unsigned int min = wordData->counts[0];
            unsigned int max = wordData->counts[0];

            // Find min and max
            for(int i = 1; i < NUM_OF_DECADES; i++) {
              if(wordData->counts[i] < min) {
                min = wordData->counts[i];
              } else if(wordData->counts[i] > max) {
                max = wordData->counts[i];
              }
            }
            
            if(commandIndex == PLOT) {    // If plot, build and print plot
              buildPlot(plot, w, min, max);
              printPlot(plot, min, max);
            } else if(commandIndex == DATA) {   // If data, print data
              printData(w);
            }
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

