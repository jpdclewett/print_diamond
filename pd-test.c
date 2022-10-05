/* Print Diamond object, test functionality.
 *
 * author: James Clewett
 * date: 18/1/2022
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

#include "pd.h"
#include "pd-internals.h"
#include "pd-test.h"

/* creates a char buffer and hands ownership to the caller.
 */
static char *loadTestBufferFromFile(const char *fname)
{
    FILE *fh;
    size_t size, read;
    char *buf;
    
    fh = fopen(fname, "r");
    if (fh == NULL)
    {
        fprintf(stderr, "WARNING: Failed to open file %s for reading\n"
                      , fname);
        return NULL;
    }
    
    /* check the file size
     */
    fseek(fh, 0, SEEK_END);
    size = ftell(fh);
    
    buf = malloc(size);
    if (buf == NULL)
    {
        fprintf(stderr, "WARNING: Failed to allocate %lu bytes for buffer\n"
                      , size);
        fclose(fh);
        return NULL;
    }
    
    fseek(fh, 0, SEEK_SET);
    read = fread(buf, 1, size, fh);
    
    if (read != size)
    {
        fprintf(stderr, "WARNING: Failued to read %lu bytes from test file %s\n"
                      , size
                      , fname);
        fclose(fh);
        free(buf);
        return NULL;
    }
    
    fclose(fh);
    
    return buf;   
}

char PD_getCurrentCharacter(PD *pd)
{
    if (pd != NULL)
        return pd->ch;
        
    return 0;
}

size_t PD_getDiamondDimensions(PD *pd)
{
    if (pd != NULL)
        return pd->dim;
        
    return 0;
}


size_t PD_getBufferSize(PD *pd)
{
    if (pd != NULL)
        return pd->size;
        
    return 0;
}


Error PD_compareWithExpectedOutput(PD *pd, char ch)
{
    char fname[64];
    char *expected;
    
    ch = tolowercase(ch);
    
    sprintf(fname, "tests/%c.txt", ch);
    
    expected = loadTestBufferFromFile(fname);
    if (expected == NULL)
    {
        fprintf(stderr, "WARNING: Failed to load expected output from %s\n"
                      , fname);
        return failure;
    }
    
    if (strncmp(expected, pd->buffer, pd->size) != 0)
    {
        fprintf(stderr, "WARNING: Buffer does not match with expected buffer: %c\n"
                      , ch);
        return failure;
    }
    
    free(expected);
    
    return success;
}
