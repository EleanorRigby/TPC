#include <stdio.h>
#include <string.h>

int denomination [] =   {1, 2, 5, 10, 20, 50 ,100};
int denom_size      =   sizeof(denomination)/(sizeof denomination[0]); 

/**
 * Coin Change Problem
 * Calculate the following sequence of fractions:
 * How many ways are there to make change for Rs. 100, if you
 * have notes for Rs. 1, Rs. 2, Rs. 5, Rs. 10, Rs. 20, Rs. 50
 * and Rs. 100.
 * 
 * 
 * 
 **/ 


/**
 * Entry Point
 */
main()
{
    
        int change_of       =   100;
        int solution        =   0;    
      
        
    solution = get_change (denomination, denom_size, change_of);
    
    printf ("Number of ways to make 100 out of given denominations is %d ", solution);
    
    return;    
    
}


/**
 * Returns the number of possible solution for set {a,b,c,d,e,f,g} where 
 * Aa+ Bb + Cc + Dd + Ee + Ff + Gg = pChangeOf. A,B,C,D,E,F,G are value of 
 * denominations.
 */
int get_change (int * pDenomination, int pSize, int pChangeOf)
{
    //case: amount or number has become zero, so this is a solution
    if (pChangeOf == 0)
        return 1;
        
    //case: amount negative , no solution , return 0.
    if (pChangeOf < 0)
        return 0;
        
    //case: coins are over
    if (pSize <= 0)
        return 0;
        
    //Number of solution = number of solution for amount n with m-1 coins +
    //number of solution for amount - mth coin for all possible coins.
    return  get_change(pDenomination,
                       pSize - 1,
                       pChangeOf) 
                       + 
            get_change(pDenomination,
                       pSize,
                       pChangeOf - pDenomination [pSize - 1]);
                         
    
}

