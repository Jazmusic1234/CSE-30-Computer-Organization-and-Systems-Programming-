/*
 * Filename: pa3.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/18/2019
 * Sources of Help: writeup, pa2, Week 7 Discussion Worksheet, Notes #6.2,
 *    GeeksforGeeks.org
 */

#include <stdio.h>
#include <string.h>
#include "pa3.h"
#include <stdlib.h>
#include <getopt.h>
#include "pa3Strings.h"
#include <errno.h>
#include <stdbool.h>

/*
 * Function Name: pa3()
 * Function Prototype: int main( int argc, char * argv[] ); 
 * Description: Parse command line arguments and start user-interactive mode 
 * Parameters: argc - number of arguments
 *             argv - command line arguments
 *
 * Side Effects: None
 * Error Conditions: if invalid flags, error
 *                   if args are in wrong format or are invalid, error
 *                   if memory allocation issues, error
 *                   if failed to buildWordTable(), error
 *                   
 * Return Value: if error occurs, return EXIT_FAILURE
 *               if user exits loop, return EXIT_SUCCESS
 */
int main( int argc, char * argv[] ) {
  
  char NULL_CHAR = '\0';
  int allowedFileSizes[] = ALLOWED_FILE_SIZES;
  int c;
  char * slots = NULL;
  char * fileSize = NULL;
  char * endPtrN;
  char * endPtrS;
  int numSlots = DEFAULT_NUM_SLOTS;
  int size = DEFAULT_FILE_SIZE;
  
  // Parse flags using getopt
  while((c = getopt(argc, argv, OPTSTRING)) != -1) {
    switch(c) {
      case HELP_FLAG:
        printf(STR_USAGE, argv[0], DEFAULT_DATA_DIR, MIN_NUM_SLOTS, 
          MAX_NUM_SLOTS, DEFAULT_NUM_SLOTS, DEFAULT_FILE_SIZE);
        return EXIT_SUCCESS;

      case NUM_SLOTS_FLAG:
        slots = optarg;

      case FILE_SIZE_FLAG:
        fileSize = optarg;

      default:
        return EXIT_FAILURE;
    }

  }

  //Check for extra args
  if(optind < argc) {
    fprintf(stderr, STR_ERR_EXTRA_ARG, argv[optind]); 
  } 

  // Convert -n and -s flags
  errno = 0;

  if(c == NUM_SLOTS_FLAG) {   // If -n flag
    numSlots = strtoul(slots, &endPtrN, NUM_SLOTS_BASE);
    
    if(errno != 0) {
      fprintf(stderr, STR_ERR_CONVERTING, STR_NUM_SLOTS_ARGNAME, slots, 
        NUM_SLOTS_BASE, strerror(errno));
      return EXIT_FAILURE;
    } else if(*endPtrN != NULL_CHAR) {    // Check for invalid chars
      fprintf(stderr, STR_ERR_NOT_INT, STR_NUM_SLOTS_ARGNAME, endPtrN, 
        NUM_SLOTS_BASE);
      return EXIT_FAILURE;
    } else if(intervalContains(MIN_NUM_SLOTS, MAX_NUM_SLOTS, numSlots) != 1) {
      fprintf(stderr, STR_ERR_NUM_SLOTS_INTERVAL, numSlots, MIN_NUM_SLOTS,
        MAX_NUM_SLOTS);
        return EXIT_FAILURE;
    }
  } else if(c == FILE_SIZE_FLAG) {    // If -s flag
    size = strtoul(fileSize, &endPtrS, SIZE_BASE);

    if(errno != 0) {
      fprintf(stderr, STR_ERR_CONVERTING, STR_SIZE_ARGNAME, fileSize,
        SIZE_BASE, strerror(errno));
        return EXIT_FAILURE;
    } else if(*endPtrS != NULL_CHAR) {
      fprintf(stderr, STR_ERR_NOT_INT, STR_SIZE_ARGNAME, endPtrS,
        SIZE_BASE);
    }
    bool validSize = false;
    for(int i = 0; i < ALLOWED_FILE_SIZES_LEN; i++) {
      if(allowedFileSizes[i] == size) {
        validSize = true;
      }
    }

    if(validSize == false) {
      fprintf(stderr, STR_ERR_SIZE_INVALID, size);
      return EXIT_FAILURE;
    }
  }
  
  
  wordTable_t table = {
    .slotPtr = NULL,
    .numSlots = numSlots
  };
  wordTable_t * tablePtr = &table;

  tableSlot_t * slot = calloc(numSlots, sizeof(struct tableSlot));
  table.slotPtr = slot;

  if(table.slotPtr == NULL) {
    fprintf(stderr, STR_ERR_MEM_EXCEEDED);
    return EXIT_FAILURE;
  }
  if(buildWordTable(tablePtr, size) == -1) {
    free(slot);
    return EXIT_FAILURE;
  }

  interactiveLoop(tablePtr);
  for(int i = 0; i < table.numSlots; i++) {
    free(tablePtr->slotPtr[i].wordDataPtr);
    free(tablePtr->slotPtr);
  }
  return EXIT_SUCCESS;

}

