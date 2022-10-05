/* Print Diamond context prototypes.
 *
 * author: James Clewett
 * date: 18/1/2022
 */
 
#ifndef PRINT_DIAMOND_H
#define PRINT_DIAMOND_H


#include "common.h"

typedef struct PD PD;

/* Create a Print Diamond context.
 * 
 * The context will be used to guard against poorly
 * formed requests.
 * 
 * params:
 *
 * returns:
 * PD *, a pointer to a Print Diamond context.
 */
PD *PD_new();

/* Clean up the Print Diamondn Context.
 * 
 * params: 
 * PD *pd, a pointer to a Print Diamond context.
 * 
 * return: 
 * void
 */
void PD_delete(PD *pd);

/* Set the current character in the
 * Print Diamond context. 
 * The character is forced to lowercase.
 * The dimensions of the diamond are recalculated.
 * The buffer size is recalculated.
 * The buffer is reallocated.
 * 
 * params:
 * PD *pd, a pointer to a Print Diamond context.
 * char ch, the desired character.
 *
 * return:
 * Error, success or failure of the operation.
 * Possible failures include, character out of range.
 * Memory allocation failure.
 */
Error PD_setChar(PD *pd, char ch);

/* Print the current buffer to stdout.
 * 
 * params:
 * PD *pd, a pointer to a Print Diamond context.
 *
 * returns:
 */
void PD_show(PD *pd);

#endif /* PRINT_DIAMOND_H */
