/*
 * Filename: processFPToken.c
 * Author: Gurkirat Singh
 * Description: This file processes float numbers to call appropriate function
 *              according to which flag was set and also prints out a prefix
 *              to the number if, for example, the number was negative. The
 *              files handles only B and E flag
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pa3.h"
#include "strings.h"

/*
 * Function name: processFPToken()
 * Function prototype: void processFPToken(char* inStr,struct argsInfo info);
 * Description: This function converts the given float number to a double first
 *              and then gets the left side of the string from the decimal 
 *              point and then the right side. It prints each side separately.
 *              The function handles error checking from conversion to char
 *              pointer to double and calls a function appropriate to 
 *              which flag was set. B flag calls printFPBinary to print out
 *              binary representation of float numbers.
 * Parameters:
 *    arg 1: char *inStr -- char pointer that is the string we need to convert
 *                            to double or float later on.
 *    arg 2: struct argsInfo info -- struct that contains info about which
 *                            input base, outputbase, and mode was set and also
 *                            what the name of the input file is if it was
 *                            included.
 * Side Effects: Conversion from double to float may result in roundoff errors
 * Error Conditions: check if char pointer was successfully converted to a 
 *                    double, if there are multiple dots in the number.
 * Return Value: None
 */
void processFPToken(char* inStr, struct argsInfo info)
{
    char* pEnd;
    char charPointer[BUFSIZ];
    double num;

    /*convert the char pointer (string) to a double*/
    num = strtod(inStr, &pEnd);
    
    /*print out the initial value that was passed to us*/
    (void)printf(STR_INPUT_STR_FMT,inStr);

    /*conversion to double was unsuccessful. Also check if there were
     *two dots in the string
     */
    if (errno == EINVAL || strlen(pEnd) != 0){
        (void)fprintf(stderr, STR_FLOAT_ENDPTR_ERR, inStr);
        return;
    }

    /*double num is too large to hold*/
    if (errno != 0){
        (void)snprintf(charPointer, BUFSIZ, "\t%s",inStr);
        perror(charPointer);
        return;
    }

    /*E flag is set*/
    if (info.mode & E_FLAG){

        /*find if the string is a negative*/
        char *neg = strchr(inStr, '-');
        if (neg != NULL){
            /*print out the minux prefix*/
            (void)printf(STR_MINUS);    
        } 

        /*check for decimal point in string and replace it with null character
         *so we can get the left side of the string
         */
        char *decPoint = strchr(inStr, '.');
        if (decPoint != NULL){
            *decPoint = '\0';
        }

        /*convert the left side of the string to a long int*/
        long convertedNum = strToLong(inStr, 10);

        /*negative the long int if it is negative*/
        if (convertedNum < 0){
            convertedNum = convertedNum * (-1);
        }

        /*print the english word representation of left side*/
        printEnglish(convertedNum);

        (void)printf(STR_DOT);

        /*loop until we find a non-zero number, until then keep printing 
         *zeros
         */
        while(*(++decPoint) == '0'){
            (void)printf(STR_ZERO);
        }
        long rightSide =  strToLong(decPoint, 10);
        
        /*print the right side of the float number*/
        if (rightSide != 0) printEnglish(rightSide);
    
    }
    (void)printf(STR_NEWLINE);

    /*B flag was set, so print the binary representation of the float number*/
    if (info.mode & B_FLAG){
        float convertedFloat = (float)num;
        printFPBinary(convertedFloat);
    }
    
}
