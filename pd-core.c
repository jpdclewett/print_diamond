/* Print Diamond object, core functionality.
 *
 * author: James Clewett
 * date: 18/1/2022
 */
 
#include <stdlib.h>
#include <stdio.h>

#include "pd.h"
#include "pd-internals.h"

 
static Error verifyCharacterRange(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return success;
    
    return failure;
}   
 

static size_t calculateDiamondDimensions(char ch)
{
   if (ch < 'a' || ch > 'z')
       return -1;
       
   /* In order to determine the dimenions of the diamond:
    * 
    * 'a' = 1
    * 'b' = 3
    * 'c' = 5 etc...
    * 
    * The magic +1 here allows for the initial 'a'.
    *
    * The dimension should always be odd - worth a bonus test.
    */
   return 2*(ch - 'a') + 1;
}
 
 
static size_t calculateBufferSize(size_t dim)
{
    /* The buffer size is based on the dimensions of the
     * diamond.  
     * 
     * Each line of the diamond will require a '\n' character.  
     * If implemented in windows there will be an additional '\r' 
     * character.
     *
     * As such the size of the buffer required is:
     */

    return dim * (dim + 1);
}
 
 
static void populateBuffer(PD *pd)
{
    int iy, ix, i;
    char out_ch;
    int mid;
    int dim = (int)pd->dim;
    
    mid = (pd->dim - 1)/2; /* recall, dim is always odd */
    
    out_ch = 'a';
    for (iy = 0  ; iy < dim ; iy ++)
    {
        /* okay, I really don't like this out by 1, 
         * it is so misleading.
         */
        for (ix = 0 ; ix < dim+1 ; ix ++)
        {
            int ch_idx = abs(mid-iy);
            
            i = ix + iy*(dim+1);
                    
            if (ix == ch_idx || ix == dim - ch_idx-1)
                pd->buffer[i] = out_ch;
            else if (ix == dim)
                pd->buffer[i] = '\n';
            else
                pd->buffer[i] = ' ';
        }   
        if (iy < mid)
            out_ch ++;
        else 
            out_ch --;
    }
}


char tolowercase(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        ch += ('a' - 'A');
    
    return ch;
}


PD *PD_new()
{
    PD *new_pd;
    
    new_pd = calloc(sizeof(PD), 1);
    if (new_pd != NULL)
    {
        /* initialise stuff 
         */
    }
    
    return new_pd;
}
 
 
void PD_delete(PD *pd)
{
   if (pd != NULL)
   {
        free(pd->buffer);
        free(pd);
   }
}


Error PD_setChar(PD *pd, char ch)
{
    Error e;
    
    if (pd == NULL)
        return failure;
        
    e = verifyCharacterRange(ch);
    if (e != success)
    {
        fprintf(stderr, "WARNING: Character %c not in ascii letter range\n"
                      , ch);
        return e;
    }
    
    ch = tolowercase(ch);
    
    pd->ch = ch;
    
    pd->dim = calculateDiamondDimensions(ch);
    
    pd->size = calculateBufferSize(pd->dim);
    
    if (pd->buffer != NULL)
        free(pd->buffer);
    
    pd->buffer = malloc(pd->size);
    if (pd->buffer == NULL)
    {
        fprintf(stderr, "WARNING: Failed to allocate %lu bytes for buffer\n"
                      , pd->size);
        return failure;
    }
    
    populateBuffer(pd);
    
    return success;
}

void PD_show(PD *pd)
{
    if (pd == NULL)
        return;
        
    fprintf(stdout, "%.*s\n", (int)pd->size, pd->buffer);
}
