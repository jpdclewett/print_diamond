/* Print Diamond object, prototypes for testing functionality.
 *
 * author: James Clewett
 * date: 18/1/2022
 */
 
#ifndef PRINT_DIAMOND_TEST_H
#define PRINT_DIAMOND_TEST_H

#include <stdlib.h>

#include "common.h"
#include "pd.h"

/* Get the Diamond dimensions, that is the 
 * width and height of a char buffer required
 * to display the whole diamond.
 * The area will always be a square with 
 * an odd side length.
 * 
 * params:
 * PD *pd, the Print Diamond context.
 * 
 * return
 * size_t, the width and height (same value).
 */
size_t PD_getDiamondDimensions(PD *pd);


/* Get the character that the Print
 * Diamond context is currently set up with.
 * 
 * Character will be lowercase.
 *
 * params: 
 * PD *pd, the Print Diamond context. 
 *
 * return:
 * char, the current character.
 */
char PD_getCurrentCharacter(PD *pd);


/* Get the buffer size of the Print
 * Diamond context.
 * The buffer will contain a text string
 * with the current diamond values.
 * 
 * params: 
 * PD *pd, the Print Diamond context. 
 *
 * return: 
 * size_t, the current buffer size.
 */
size_t PD_getBufferSize(PD *pd);

/* Compare the buffer obtained for the
 * current context, with a previously calculated
 * buffer loaded from a file.
 * The previously calculated buffer has been
 * manually inspected to ensure that the
 * results match with the desired outcome.
 * 
 * params: 
 * PD *pd, the Print Diamond context.
 * char ch, the character to be compared.
 * 
 * return: 
 * Error, the success of failure of the comparison.
 */
Error PD_compareWithExpectedOutput(PD *pd, char ch);


#endif /* PRINT_DIAMOND_TEST_H */
