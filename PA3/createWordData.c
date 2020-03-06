/*
 * Filename: createWordData.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/13/2019
 * Sources of Help: writeup, tutorialspoint.com
 */

#include <stdio.h>
#include <string.h>
#include "pa3.h"

/*
 * Function Name: createWordData()
 * Function Prototype: void createWordData( wordData_t * wordData, 
 *      const char * wordStr, unsigned int decade, unsigned int count );
 * Description: Populates fields of wordData struct to represent wordStr
 * Parameters: wordData - wordData struct to fill
 *             wordStr - word to fill wordData with
 *             decade - year
 *             count - number to fill wordData at decade index with
 *
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 */

void createWordData( wordData_t * wordData, const char * wordStr, 
                     unsigned int decade, unsigned int count ) {

  unsigned int index = (decade - MIN_DECADE) / YEARS_IN_DECADE;
  char NULL_CHAR = '\0';
  strncpy(wordData->word, wordStr, MAX_WORD_SIZE);
  wordData->word[MAX_WORD_SIZE - 1] = NULL_CHAR;

  for(int i = 0; i < NUM_OF_DECADES; i++) {
    wordData->counts[i] = 0;
  }

  wordData->counts[index] = count;

  wordData->hashValue = computeHash(wordStr);

}

