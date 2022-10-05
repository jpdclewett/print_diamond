#include <gtest/gtest.h>

extern "C"
{
#include "common.h"
#include "pd.h"
#include "pd-test.h"
}

using namespace ::testing;

TEST(PrintDiamond, pd_verify_object_creation)
{
    PD *pd;
    
    pd = PD_new();
    if (pd == NULL)
    {
        ASSERT_TRUE(0);
    }
    
    PD_delete(pd);
}

TEST(PrintDiamond, pd_verify_character_lowercase)
{
    PD *pd;
    char ch;
    
    pd = PD_new();
    if (pd == NULL)
    {
        ASSERT_TRUE(0);
    }
    
    for (ch = 'A' ; ch <= 'Z' ; ch ++)
    {
        PD_setChar(pd, ch);
        
        ASSERT_TRUE(PD_getCurrentCharacter(pd) == ch - 'A' + 'a');
    }
    
    PD_delete(pd);
}

TEST(PrintDiamond, pd_verify_diamond_dimensions)
{
    PD *pd;
    char ch;
    
    pd = PD_new();
    if (pd == NULL)
    {
        ASSERT_TRUE(0);
    }
    
    for (ch = 'a' ; ch <= 'z' ; ch ++)
    {
        size_t ans;
        
        PD_setChar(pd, ch);
        
        /* The diamond must have equal width and height.
         * by observation:
         * 'a' is 1 character wide
         * 'b' is 3 characters wide
         * 'c' is 5 characters wide etc...
         *
         * As such the dimensions of the output are given by:
         */
        ans = 2 * (ch - 'a') + 1;
        
        ASSERT_TRUE(PD_getDiamondDimensions(pd) == ans);
        
        /* Bonus test: verify that the dimension is always even...
         */
        ASSERT_TRUE((PD_getDiamondDimensions(pd) % 2) == 1);
    }
 
    PD_delete(pd);
}



TEST(PrintDiamond, pd_verify_buffer_size)
{
    PD *pd;
    char ch;
    
    pd = PD_new();
    if (pd == NULL)
    {
        ASSERT_TRUE(0);
    }
    
    for (ch = 'a' ; ch <= 'z' ; ch ++)
    {
        size_t dim;
        size_t ans;
        
        PD_setChar(pd, ch);
        
        dim = PD_getDiamondDimensions(pd);
        
        /* The buffer size is based on the dimensions of the
         * diamond.  
         * 
         * Each line of the diamond will require a '\n' character.  
         * If implemented in windows there will be an additional '\r' 
         * character.
         *
         * As such the size of the buffer required is:
         */
         ans = dim * (dim + 1);
         
         ASSERT_TRUE(PD_getBufferSize(pd) == ans);
    }
    
    PD_delete(pd);
}

/* Test files containing the desired output 
 * are provides in tests/a.txt .. z.txt.
 */
TEST(PrintDiamond, pd_match_expected_results)
{
    PD *pd;
    char ch;
    
    pd = PD_new();
    if (pd == NULL)
    {
        ASSERT_TRUE(0);
    }
    
    for (ch = 'a' ; ch <= 'z' ; ch ++)
    {
        PD_setChar(pd, ch);
        
        PD_show(pd);
        
        ASSERT_TRUE(PD_compareWithExpectedOutput(pd, ch) == success);
    }
    
    /* repeat for upper case characters
     */
    for (ch = 'A' ; ch <= 'Z' ; ch ++)
    {
        PD_setChar(pd, ch);
        
        PD_show(pd);
        
        ASSERT_TRUE(PD_compareWithExpectedOutput(pd, ch) == success);
    }
    
    PD_delete(pd);
}

TEST(PrintDiamond, pd_badly_formed_request)
{
    PD *pd;
    Error e;
    
    pd = PD_new();
    if (pd == NULL)
    {
        ASSERT_TRUE(0);
    }
    
    /* use character not in ascii letter range
     */
    e = PD_setChar(pd, '#');

    ASSERT_TRUE(e ==  failure);
    
    PD_delete(pd);
}

