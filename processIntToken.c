/*
 * Filename: processIntToken.c
 * Author: Gurkirat Singh
 * Description: This file calls other functions if a specific flag was set.
 *              For example, if O flag was set, then for base 2 the number
 *              would be printed in binary, and such. It handles printing
 *              of the prefix and also delegating which methods should
 *              be initiated. It processes each integer token individually.
 */

#include <errno.h>
#include <stdio.h>
#include "pa3.h"
#include "strings.h"

/*Constants to check if the output base flag was set for binary,octal,
 *or hex bases
 */
#define BINARY 2
#define OCTAL 8
#define HEX 16

/*
 * Function: processIntToken()
 * Function prototype: void processIntToken(char* inStr,struct argsInfo info);
 * Description: This function processes the number that was passed in to us
 *              and then calls different functions appropriately based on
 *              which flags were set. It checks BASE_MASK for outputBases
 *              and prints the num in words if E flag was set. It handles
 *              integer validation for the num and prints out the prefixes
 *              to different bases
 * Parameters: 
 *    arg 1: char *inStr -- char pointer (string) that is the num we need
 *                            to other functions to print it in different
 *                            formats.
 *    arg 2: struct argsInfo info -- Entire struct that holds infomation
 *                            regarding which flags were set, the name of the
 *                            file if it was set, and the input and output
 *                            bases.
 * Side Effects: Char pointer parameter can be negative and needs to be
 *                handled differently.
 * Error Conditions: Checks if the char pointer is successfully converted
 *                to a long int
 * Return value: None
 */
void processIntToken(char *inStr, struct argsInfo info)
{
    int isNeg = 0;    /*lets you know if number was negative*/
    int counter;
    char charPointer[BUFSIZ];

    /*convert char pointer to a long it*/
    long convertedNum = strToLong(inStr, info.inputBase);

    /*Just print what was passed in to us*/
    (void)printf(STR_INPUT_STR_FMT, inStr);
    
    /*Error occurred because string was not an int*/
    if (errno == EINVAL){
        (void)fprintf(stderr, STR_INT_ENDPTR_ERR, inStr,info.inputBase);
        return;
    }

    /*Int is too large*/
    if (errno != 0){
        (void)snprintf(charPointer,BUFSIZ,"\t%s",inStr);
        perror(charPointer);
        return;
    }

    /*Negative number was passed; Store the positive of it in a separate
     *variable
     */
    if (convertedNum < 0){
        convertedNum = convertedNum * (-1);
        isNeg = 1;
    }
    
    /*E flag was set. Call printEnglish by passing in the long int
     *we converted. printEnglish doesn't take in negative numbers, handle
     *negative numbers correctly
     */
    if (info.mode & E_FLAG){
        
        /*print minus word if number is negative*/
        if (isNeg){
            (void)printf(STR_MINUS);
        }
        printEnglish(convertedNum);
        (void)printf(STR_NEWLINE);

    }

    /*O flag was set*/
    if (info.mode & O_FLAG){

        /*Loop through outputBases that were set from min base to max base*/
        for(counter = MIN_BASE; counter <= MAX_BASE; counter++){

            /*outputBase was set for this num*/
            if(info.outputBases & BASE_MASK(counter)){

                /*Base 2 was entered*/
                if(counter == BINARY){
                    
                    /*print the num in binary representation*/
                    if (isNeg)
                        printIntBinary(-convertedNum);
                    else
                        printIntBinary(convertedNum);

                }else if (counter == OCTAL){
                    
                    /*Print octal representation of num with '0' prefix*/
                    if (isNeg) (void)printf(STR_NEG_PREFIX);
                    (void)printf(STR_OCT_PREFIX);
                    printBase(convertedNum, counter);

                }else if (counter == HEX){
                    
                    /*Hex representation of num with '0x' prefix*/
                    if (isNeg) (void)printf(STR_NEG_PREFIX);
                    (void)printf(STR_HEX_PREFIX);
                    printBase(convertedNum, counter);

                }else{
                    
                    /*Prints the num into all bases that were set*/
                    if (isNeg) (void)printf(STR_NEG_PREFIX);
                    printBase(convertedNum, counter);
                }
                
                (void)printf(STR_NEWLINE);
            }

        }

    }

}
