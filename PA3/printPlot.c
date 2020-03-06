/*
 * Filename: printPlot.c
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/18/2019
 * Sources of Help: writeup
 */

#include <stdio.h>
#include <string.h>
#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function Name: printPlot()
 * Function Prototype: void printPlot( char plotArr[PLOT_ROWS][PLOT_COLS], 
 *      unsigned int minCount, unsigned int maxCount );
 * Description: Print graph that was initialized in buildPlot() to stdout
 * Parameters: plotArr - 2D-array containing data for word
 *             minCount - minimum count of all decades
 *             maxCount - maximum count of all decades
 *
 * Side Effects: Prints plot to stdout
 * Error Conditions: None
 *                   
 * Return Value: None
 */
void printPlot( char plotArr[PLOT_ROWS][PLOT_COLS], unsigned int minCount,
                unsigned int maxCount ) {

  unsigned int percent = PERCENTAGE_FACTOR;

  for(int i = 0; i < PLOT_ROWS; i++) {
    
    if(i == 0) {  // If fisrt row
      printf(STR_PLOT_ROW_BOUND, maxCount, percent, plotArr[i]);
    } else if(i == PLOT_ROWS - 1) {  // If last row
      printf(STR_PLOT_ROW_BOUND, minCount, percent, plotArr[i]);
    } else {
      printf(STR_PLOT_ROW, percent, plotArr[i]);
    }

  }

  printf(STR_PLOT_X_AXIS);

}

