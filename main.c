/*
 * Filename: main.c
 * Author: Gurkirat Singh
 * Description: This file fills information into the struct by calling 
 *              setFlags and handles error checking to print out usage
 *              messages if H flag is set. It allocates memory by using
 *              malloc for the char pointers and also for the char pointer
 *              array that contains those char pointers. This program
 *              enables the user to add arguments using the file or 
 *              from the command line directly. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa3.h"
#include "strings.h"

/*
 * Function name: main()
 * Function prototype: int main(int argc, char* argv[]);
 * Description: This function takes input from the file or from the command
 *              line. If it is from the file, then it allocates space
 *              using malloc and adding more space using realloc after each
 *              tokenization of the string it gets from the file. If reading
 *              from the command line, it uses realloc to allocate an array of
 *              input strings. The function also determines and handles errors
 *              telling you if the input should be treating as an int or 
 *              as a floatint point number.
 * Parameters:
 *    arg 1: int argc -- number of arguments passed in
 *    arg 2: char *argv[] -- all the arguments as char pointers
 *                inside an array
 * Side Effects: Malloc and realloc errors can cause some integers or float
 *                to not get printed at all. Must free all memory
 *                allocated
 * Error Conditions: checks if file (if passed in) is null or not, and also
 *                print the Usage of the program if H flag was set.
 * Return value: 0 indicating successful execution
 */
int main(int argc, char* argv[])
{
    
    /*turn off buffering in stdout*/
    (void) setvbuf(stdout, NULL, _IONBF, 0);
    struct argsInfo argsInfo;
    char ** inputStrings;
    char buf[BUFSIZ];
    int counter, freeRunner, index, stringsRead = 0;
    char *tokenResult, *strTokenizer, *storedToken;
    FILE *file;
    char *bytesStored;

    /*initialize our char double pointer array using malloc. It saves space in
     *the heap for us
     */
    inputStrings = (char **) malloc(sizeof(char*));

    /*Initialize and fill the struct with values we got from command line*/
    argsInfo = setFlags(argc, argv);
 
    /*Somewhere an error occurred, so just print the Usage of the program*/
    if (argsInfo.mode & H_FLAG){
        (void)fprintf(stderr, STR_USAGE_MSG, argv[0]);
        return 0;
    }

    /*We are reading the numbers from the file*/
    if (argsInfo.mode & F_FLAG){
        
        /*try to open the file if exists*/
        file = fopen(argsInfo.inFileStr, "r");
        if (file != NULL){
            
            /*Loop through each line of the file using fgets until the very
             *last number in the file
             */
            while ((storedToken = fgets(buf, BUFSIZ, file)) != NULL){
                
               /*Tokenize each line if it contains multiple numbers using 
                *our file token separater delimiter
                */
                while((tokenResult=strtok_r(storedToken,STR_FILE_TOK_SEPARATOR,
                    &strTokenizer)) != NULL)
                {
                    /*store space in heap from the length of the string*/
                    bytesStored = (char*) malloc(strlen(tokenResult) + 1);

                    /*print error if malloc returned Null*/
                    if (bytesStored == NULL){
                        perror(STR_MALLOC_ERR);
                        return 0;
                    }

                    /*copy the token we extracted from the string and put it
                     *in the heap space we allocated first
                     */
                    (void)strncpy(bytesStored, tokenResult, 
                        strlen(tokenResult) + 1);
                    
                    /*reallocate space each time we have a new token to place
                     *in memory
                     */
                    inputStrings = (char**)realloc(inputStrings,
                                        (stringsRead + 1)*sizeof(char*));
                    
                    /*Realloc error occurred*/
                    if(inputStrings == NULL){
                        perror(STR_REALLOC_ERR);
                        return 0;
                    }

                    /*put the char pointer (string) inside a char pointer
                     *array
                     */
                    inputStrings[stringsRead] = bytesStored;
                    stringsRead++;
                    
                    /*makes sures the next time we tokenize, the same string
                     *is not passed again
                     */
                    storedToken = NULL;
                }
            }
        }else{

            /*file couldn't be opened or was not found*/
            (void)printf(STR_TAB);
            perror(argsInfo.inFileStr);
        }

    }else{
        /*Reading input from the command line*/
        index = optind;

        /*Loop until the very end of the number of arguments we have*/
        while (index < argc){

            /*store the argument inside a char double pointer array*/
            inputStrings[stringsRead] = argv[index];
            /*realloc space for the length of the array*/
            inputStrings = (char**) realloc(inputStrings, stringsRead + 1);
            stringsRead++;
            index++;
        }

    }
    
    /*Runs the length of the char** array and figures out if each of the 
     *numbers is a whole integer or a float and appropriately calls
     *processIntToken vs. processFPToken, respectively.
     */
    for (counter = 0; counter < stringsRead; counter++){
        
        /*find out if there is a decimal pointer in the string*/
        char * strDot = strchr(inputStrings[counter], '.');
        if (strDot){
            
            /*number is a float*/
            processFPToken(inputStrings[counter], argsInfo);
        }else{
            /*number is an integer*/
            processIntToken(inputStrings[counter], argsInfo);
        }

    }
    
    /*Loop through the length of the array and free space for each 
     *char pointer, which is our string in the array
     */
    if (argsInfo.mode & F_FLAG){
        for (freeRunner = 0; freeRunner < stringsRead; freeRunner++){
            free(inputStrings[freeRunner]);
        }
    }

    /*free the space for the array itself*/
    if (inputStrings)
        free(inputStrings);

    /*0 for successful execution*/
    return 0;
}
