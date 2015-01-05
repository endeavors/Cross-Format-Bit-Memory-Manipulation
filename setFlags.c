/*
 * Filename: setFlags.c
 * Author: Gurkirat Singh
 * Description: This file sets the flags on the number passed in by OR-ing the
 *              the value of the flag with the mode set in the struct, which
 *              is an unsigned char. It processes command line options using
 *              getopt, tokenizes the line if o flag is and then stores the
 *              calculated value as the outputBase in the struct.
 */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pa3.h"
#include "strings.h"


/* global variable to keep track of there was an error with end poitner
 * when converting string to long */
int ptrError = EINVAL;

/*
 * Function name: setFlags()
 * Function prototype: struct argsInfo setFlags(int argc, char*argv[]);
 * Description: This function handles most of error checking of whether
 *              the passed paramter is a valid integer and then sets
 *              option flags accordingly by setting the appropriate bit
 *              int the mode of the struct. It handles range check of the
 *              base and also sets the outputBase using the BASE_MASK
 *              option.
 * Parameters:
 *    arg 1 -- int argc -- number of arguments on the command line
 *    arg 2 -- char *argv[] -- arguments passed in on the command line
 * Side Effects: prints out different error handling messages if 
 *              for example, file and number on the command line are 
 *              entered, invalid int, out of range,etc
 * Error Conditions: out of range, not an int, both file and numbers
 *              are entered on the command line,no input is entered, etc.
 * Return Value: struct itself
 */
struct argsInfo setFlags(int argc, char* argv[])
{
    struct argsInfo argsInfo;    /*struct that we need to return*/
    (void)memset(&argsInfo, 0, sizeof(argsInfo)); /*clear the struct*/
    int iIsSet = 0;
    int oIsSet = 0;
    int fIsSet = 0;
    int c;
    char *storedOArg, *storedIArg;

    /*get one flag at a time and process it to set its option for the num*/
    while((c = getopt(argc, argv,STR_GETOPT_OPTIONS)) != -1){
       
        /*set the appropriate bit accordingly to which flag value was entered*/
        switch(c){
            /*case if no input is added at all*/
            case '?':
                argsInfo.mode = argsInfo.mode | H_FLAG;
                return argsInfo;

            case 'h':
                argsInfo.mode = argsInfo.mode | H_FLAG;
                return argsInfo;

            case 'e':
             
                argsInfo.mode = argsInfo.mode | E_FLAG;
                break;

            case 'b':
                argsInfo.mode = argsInfo.mode | B_FLAG;
                break;

            case 'i':
                argsInfo.mode = argsInfo.mode | I_FLAG;
                storedIArg = strdup(optarg); /*create a string duplicate*/
                iIsSet = 1;
                break;

            case 'o':
                argsInfo.mode = argsInfo.mode | O_FLAG;
                oIsSet = 1;
                storedOArg = strdup(optarg);
                break;

            case 'f':
                argsInfo.mode = argsInfo.mode | F_FLAG;
                argsInfo.inFileStr = optarg; /*store the name of the file*/
                fIsSet = 1;
                break;

        }

    }

    /*I Flag was entered*/
    if (iIsSet){
        
        /*convert the string to a long int*/
        long num = strToLong(storedIArg, 0 );

        /*check if num is in min and max base range*/
        int range = checkRange(num, MIN_BASE, MAX_BASE);
        
        /*Not an integer. Set H Flag if an error occurs*/
        if (errno == EINVAL){
            (void)fprintf(stderr, STR_INBASE_ENDPTR_ERR,storedIArg);
            argsInfo.mode = argsInfo.mode | H_FLAG;

        }else if (range == 0){

            (void)fprintf(stderr, STR_INBASE_BAD_RANGE,num,MIN_BASE,MAX_BASE);
            argsInfo.mode = argsInfo.mode | H_FLAG;
        }else{

            /*set the input base inside the struct if num passes all error 
             *checks
             */
            argsInfo.inputBase = num;
        }

    }else{
        /*Default input base value is 10*/
        argsInfo.inputBase = DEFAULT_BASE;

    }

    /*O Flag was set*/
    if (oIsSet){
        char *strTokenizer, *tokenResult;

        /*tokenize multiple bases one at a time*/
        tokenResult = strtok_r(storedOArg,STR_OUTBASE_TOK_SEPARATOR,
            &strTokenizer);
        
        do{
            /*convert the base to a long int*/
            long tokenNum = strToLong(tokenResult, 0);
            
            /* An error occurred */
            if (errno == EINVAL){
                (void)fprintf(stderr, STR_OUTBASE_ENDPTR_ERR,tokenResult);
                argsInfo.mode = argsInfo.mode | H_FLAG;
                break;
            }
            /*check if the base is in base min and max range*/
            int range = checkRange(tokenNum, MIN_BASE, MAX_BASE);
            
            /*base was out of range(2-36)*/
            if (range == 0){
                (void)fprintf(stderr,STR_OUTBASE_BAD_RANGE,tokenNum,MIN_BASE,
                    MAX_BASE);
                argsInfo.mode = argsInfo.mode | H_FLAG;
                break;
            }else{
                
                /*set appropriate bit using BASE_MASK for outputBase of that
                 *num*/
                argsInfo.outputBases = argsInfo.outputBases | 
                    BASE_MASK(tokenNum);
    
            }

        /*continue looping to tokenize until out of characters*/
        } while((tokenResult = strtok_r(NULL,STR_OUTBASE_TOK_SEPARATOR,
                            &strTokenizer)) != NULL); 

    }

    /*only file or command line arguments for number can be passed in*/
    if (fIsSet && optind < argc){
        (void)fprintf(stderr, STR_FILE_AND_ARGS_ERR);
        argsInfo.mode = argsInfo.mode | H_FLAG;
    }

    /*Must at least enter a number on the command line or the file but not
     *both
     */
    if (argc == optind && !fIsSet){
        (void)fprintf(stderr,STR_NO_INPUT_ERR);
        argsInfo.mode = argsInfo.mode | H_FLAG;
    }

    /*return the entire struct*/
    return argsInfo;

}
