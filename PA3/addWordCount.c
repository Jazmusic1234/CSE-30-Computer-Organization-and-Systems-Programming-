/*
 * Filename: addWordCount.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/11/2019
 * Sources of Help: writeup
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function Name: addWordCount()
 * Function Prototype: int addWordCount( tableSlot_t * slot, 
 *      const char * word, unsigned int decade, unsigned int count );
 * Description: Add count for word and the decade to tableSlot
 * Parameters: slot - slot to add to
 *             word - word to create wordData struct for
 *             decade - year to calculate index from
 *             count - item to set counts array at calculated index to
 *
 * Side Effects: print error message to stderr if error
 * Error Conditions: if realloc fails, print error message to stderr and free
 *      slot's wordDataPtr
 * Return Value: if error, return -1
 *               else, return 0
 */
int addWordCount( tableSlot_t * slot, const char * word, unsigned int decade, 
    unsigned int count ) {

  unsigned int index = (decade - MIN_DECADE) / YEARS_IN_DECADE;

  // Initialize new wordData_t
  wordData_t w;

  // Fill new wordData_t
  createWordData(&w, word, decade, count);

  wordData_t * slotWordData = bsearch(&w, slot->wordDataPtr, slot->numWords, 
      sizeof(struct wordData), compareWordData);
  
  if(slotWordData != NULL) {  // Already have a slot for this word
    slotWordData->counts[index] = slotWordData->counts[index] + count;
    return 0;
  } else {  // No slot for this word
    struct wordData * temp = realloc(slot->wordDataPtr, 
        (slot->numWords + 1) * sizeof(struct wordData));
    
    // Array was not resized successfully
    if(temp == NULL) {
      printf(STR_ERR_MEM_EXCEEDED);
      free(slot->wordDataPtr);
      slot->wordDataPtr = NULL;
      return -1;
    } else {  // Array resized successfully
      temp[slot->numWords] = w;
      slot->wordDataPtr = temp;
      slot->numWords += 1;
      qsort(&(slot->wordDataPtr), slot->numWords, sizeof(w), compareWordData);      
      return 0;
    }
  }


}

