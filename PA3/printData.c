/*
 * Filename: printData.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/18/2019
 * Sources of Help: writeup
 */

#include <stdio.h>
#include <string.h>
#include "pa3.h"
#include "pa3Strings.h"
#include <stdbool.h>

/*
 * Function Name: printData()
 * Function Prototype: void printData( const wordData_t * word );
 * Description: Prints out word stats in tabular format to stdout
 * Parameters: word - wordData_t to get data from
 *
 * Side Effects: Print stats to stdout
 * Error Conditions: None
 *                   
 * Return Value: None
 */
void printData( const wordData_t * word ) {

  printf(STR_STATS_HEADER);

  unsigned int maxDecade = 0;
  bool tie = false;

  for(int i = 0; i < NUM_OF_DECADES; i++) {
    if(word->counts[i] > word->counts[maxDecade]) {
      maxDecade = i;
      tie = false;
    } else if(word->counts[i] == word->counts[maxDecade]) {
      tie = true;
      maxDecade = i;
    }
    printf(STR_STATS_FMT_COUNT, MIN_DECADE + (i * YEARS_IN_DECADE), 
      word->counts[i]);
  }

  if(tie == true) {
    printf(STR_HIGH_COUNT, word->word, STR_MOST_RECENT, 
      MIN_DECADE + (maxDecade * YEARS_IN_DECADE), word->counts[maxDecade]);
  } else {
    printf(STR_HIGH_COUNT, word->word, "", 
      MIN_DECADE + (maxDecade * YEARS_IN_DECADE), word->counts[maxDecade]);
  }

}

