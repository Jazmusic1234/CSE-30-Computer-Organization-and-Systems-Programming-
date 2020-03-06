/*
 * Filename: buildWordTable.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/18/2019
 * Sources of Help: writeup, Week 5 Discussion Worksheet, Week 7 Discussion
 *    Worksheet, piazza
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function Name: buildWordTable()
 * Function Prototype: int buildWordTable( wordtable_t * table,
 *      unsigned int size ); 
 * Description: Build table by reading in data from files of specified size 
 * Parameters: table - wordTable_t to build
 *             size - size of files to read in
 *
 * Side Effects: None
 * Error Conditions: error when opening a file
 *                   error when tokenizing line into word, decade, and count
 *                   error when parsing decade and count into numbers
 *                   error when adding word to table
 *                   
 * Return Value: if any addWordCount() fails, return -1
 *               else, return 0
 */
int buildWordTable( wordTable_t * table, unsigned int size ) {

  char NULL_CHAR = '\0';
  char buffer[BUFSIZ];
  for(int i = (int)FIRST_LETTER; i < (int)LAST_LETTER; i++) {
    //snprintf(buffer, BUFSIZ, STR_PATH_JOIN, DEFAULT_DATA_DIR, (char)i, size);
    snprintf(buffer, BUFSIZ, STR_PATH_JOIN, "/home/linux/ieng6/cs30x/cs30xax/temp", (char)i, size);

  
    // Open each file and read it 
    errno = 0;
    FILE * currFile = fopen(buffer, "r");

    // If file can't be opened
    if(errno != 0) {
      fprintf(stderr, STR_ERR_OPENING_FILE, buffer, strerror(errno));
      continue;
    }
    
    // Read each line of file, only BUFSIZ chars each line
    int lineNum = 1;
    char line[BUFSIZ];
    char * wordRead;
    char * decadeRead;
    char * countRead;
    char * endPtrDecade;
    char * endPtrCount;
    unsigned int decade;
    unsigned int count;
    unsigned int slotIndex;

    while(fgets(line, BUFSIZ, currFile) != NULL) {
      // Replace newline character with NULL character
      char * newline = strchr(line, NEWLINE_CHAR);
      if(newline != NULL) {
        *newline = NULL_CHAR;
      }
      
      printf("%d\n", lineNum);
      printf("%s\n", line);
      // Split line into word, decade, and count
      wordRead = strtok(line, DELIMS);
      decadeRead = strtok(NULL, DELIMS);
      countRead = strtok(NULL, DELIMS);
      printf("%s, %s, %s\n", wordRead, decadeRead, countRead);

      // If error parsing line
      if(wordRead == NULL || decadeRead == NULL || countRead == NULL) {
        fprintf(stderr, STR_ERR_PARSING_LINE, lineNum, buffer, line);
        continue;
      }

      // Convert decade and count to unsigned int
      errno = 0;
      decade = strtoul(decadeRead, &endPtrDecade, DECADE_BASE); 
      count = strtoul(countRead, &endPtrCount, COUNT_BASE);

      // Check for number conversion errors
      if(errno != 0 || *endPtrDecade != NULL_CHAR || 
        *endPtrCount != NULL_CHAR) {
        fprintf(stderr, STR_ERR_PARSING_LINE, lineNum, buffer, line);
        continue;
      }  
      
      // Add word, decade, and count to table
      slotIndex = findSlotIndex(wordRead, table->numSlots);
      int add = addWordCount(&(table->slotPtr[slotIndex]), wordRead, decade, 
        count);
      if(add == -1) {   // If add fails, close file and return -1
        fclose(currFile);
        return -1;
      }     
      lineNum++;
    }
    fclose(currFile);
  }
  return 0;
}

