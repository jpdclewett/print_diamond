/* Print Diamond entry point
 * 
 * author: James Clewett
 * date: 18/01/2022
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "pd.h"



int main (int argc, char** argv)
{
    char ch;
    char *out;
    PD *pd;
    Error e;
    int resetTests = 0;
    
    if (argc != 2)
    {
        fprintf(stdout, "Usage: Please enter pd <character>.\n");
        return usage_alert;
    }
    
    resetTests = strcmp(argv[1], "RESET_TESTS") == 0;

    pd = PD_new();
    if (pd == NULL)
    {
        fprintf(stderr, "Failed to initialise Print Diamond object\n");
        return failure;
    }
    
    if (!resetTests)
    {
        ch = argv[1][0];
    
        e = PD_setChar(pd, ch);
        if (e != success)
        {
            PD_delete(pd);
            return e;
        }
        
        out = PD_outputDiamond(pd);
        if (out == NULL)
        {
            fprintf(stderr, "Failed to produce output buffer\n");
            PD_delete(pd);
            return failure;
        }
        
        fprintf(stdout,"%s", out); 
    
        free(out);
    }
    else
    {
        PD_resetTestFiles(pd);
    }
    
    
    (void)PD_test(pd);
    
    PD_delete(pd);
    
    return success;
}
