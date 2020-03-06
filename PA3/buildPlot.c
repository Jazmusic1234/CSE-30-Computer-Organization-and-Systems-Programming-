/*
 * Filename: buildPlot.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/18/2019
 * Sources of Help: writeup
 */

#include <stdio.h>
#include <string.h>
#include "pa3.h"

/*
 * Function Name: buildPlot()
 * Function Prototype: void buildPlot( char plotArr[PLOT_ROWS][PLOT_COLS], 
 *      const wordData_t * word, unsigned int minCount, unsigned int maxCount );
 * Description: Populate 2D-array that contains plotted data for data in word
 * Parameters: plotArr - 2D-array containing data for word
 *             word - wordData_t to get data from
 *             minCount - minimum count of all decades
 *             maxCount - maximum count of all decades
 *
 * Side Effects: None
 * Error Conditions: None
 *                   
 * Return Value: None
 */

void buildPlot( char plotArr[PLOT_ROWS][PLOT_COLS], const wordData_t * word,
                unsigned int minCount, unsigned int maxCount ) {

  unsigned int truncMin = minCount / PERCENTAGE_FACTOR;
  unsigned int truncMax = maxCount / PERCENTAGE_FACTOR;
  unsigned int truncCount;
  unsigned int percentage;
  unsigned int rowIndex;
  char NULL_CHAR = '\0';

  for(int i = 0; i < PLOT_COLS - 1; i++) {
      if(i % COL_SEPARATION == 0) {
        for(int j = 0; j < PLOT_ROWS; j++) {
          plotArr[j][i] = PLOT_SPACE_CHAR;  
        } 
      } else {
        truncCount = word->counts[i] / PERCENTAGE_FACTOR;
        if(truncMin == 0 && truncMax == 0) {
          percentage = 0;
        } else if(truncMin == truncMax) {
          percentage = PERCENTAGE_FACTOR;
        } else {
          percentage = ((truncCount - truncMin) * PERCENTAGE_FACTOR) / (truncMax - truncMin);
        }

        rowIndex = PERCENTAGE_FACTOR - (percentage / ROW_RESOLUTION);

        for(int j = 0; j < PLOT_ROWS; j++) {
          if(j == rowIndex) {
            plotArr[j][i] = PLOT_LINE_CHAR;
          } else {
            plotArr[j][i] = PLOT_SPACE_CHAR;
          }
        }
      }

  }
  
  for(int k = 0; k < PLOT_ROWS; k++) {
    plotArr[k][PLOT_COLS - 1] = NULL_CHAR;
  }
  

}

