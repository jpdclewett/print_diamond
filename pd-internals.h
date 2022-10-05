/* Print Diamond object, internal structure and functions.
 *
 * author: James Clewett
 * date: 18/1/2022
 */
 
#ifndef PRINT_DIAMOND_INTERNALS_H
#define PRINT_DIAMOND_INTERNALS_H

#include <stdlib.h>

#include "pd.h"
 
struct PD
{
   size_t dim;   /* width and height of the diamond */
    
   char ch;      /* the current character */ 
   
   size_t size;  /* the size of the output buffer 
                  * into which the diamond is printed */
                  
   
   char *buffer; /* text buffer to contain the printed
                  * diamond */
};
 
 
/* convert character to lower case.
 *
 * params:
 * char ch, ascii character code.
 *
 * return:
 * if the character is in the range A..Z, then
 * it is returned as a..z.  
 * otherwise the character is left unchanged.
 */
char tolowercase(char ch);

#endif /* PRINT_DIAMOND_INTERNALS_H */
