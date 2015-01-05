/*
 * Filename: checkRange.s
 * Author: Gurkirat Singh
 * Description: SPARC assembly routine to check if the number fits in the
 *		given range.
 *		Called from main()
 */

 	.global checkRange	!Declare global variable so we can access it
				!from inside main function

	.section ".text"	!Everything below will be in text section"

/*
 * function name: checkRange()
 * Function prototype: int checkRange(long value,long minRange,long maxRange);
 * Description: Checks if the value of the first argument is in the range that
 *		is passed in. It returns 0 for false and 1 if it is true.
 * Paramters:
 *	arg 1: long value -- value that we will if it fits in the range
 *	arg 2: long minRange -- minimum range value that number can be
 *	arg 3: long maxRange -- maximum range value that number can be
 * 
 * Side Effects: None
 * Error Conditions: If the number is not in range, we will return an error
 *			later on inside the main function
 * Return Value: Returns 0 if value is not in range, 1 if it is.
 * 
 * Registers used:
 *	%i0 - arg 1 -- value that needs to be checked if it is in range;
 *			also use this return the result back.
 *	%i1 - arg 2 -- number that holds our desired minimum value
 *	%i2 - arg 3 -- number that holds our desired maximum value
 *
 */

checkRange:
	save	%sp, -96, %sp	!save caller's window
	cmp	%i0, %i1	!compare the original value with the minimum
				!range value
	bge	checkMaxRange	!if the original vaue is greater than or equal to
				!than min range value,then check for max range
	nop			!delay slot

	ba	notInRange	!number is less than min range value,send back
				!out of range result
	nop

checkMaxRange:
	cmp	%i0, %i2	!compare original value with max range value
	ble	isInRange	!if original value is less than or equal to
				!max range,then the value is in range
	nop
	
	ba	notInRange	!value is more than max range value(not
				!in range)
	nop

isInRange:
	mov	1, %i0		!store 1 in input register since value is in
				!range
	ba	sendResultBack	!branch to send back the result
	nop

notInRange:
	mov	0, %i0		!0 for not in range
	ba	sendResultBack	!branch to send back the not in range result
	nop

sendResultBack:
	ret			!return from subroutine
	restore			!restore caller's window
