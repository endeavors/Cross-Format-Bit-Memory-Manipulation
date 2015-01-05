/*
 * Filename: printIntBinary.s
 * Author: Gurkirat Singh
 * Description: Cycles through the long number and prints 1 if bit is 1
 *		or 0 if the bit is 0 using printf. A space character is 
 *		printed between every 4 bits. This program uses bit mask
 *		of 1 and shifts left logical to extract each bit after it is 
 *		"and-ed" using the bitwise & operator.
 */

BITMASK = 0x80000000		!bitmask of 1 to get most significant bit		
NEWLINE = '\n'
SPACE = ' '
FOUR = 4
INTEGER_BIT = 32		!counter to keep track when to switch to next
				!index

 	.global printIntBinary	!Declare global variable so we can call it from
				!another file
	.section ".data"

fmt:	.asciz "%d"
nwLine:	.asciz "%c"

	.section ".text"	!The text segment begins here

/*
 * Function: printIntBinary()
 * Function prototype: void printIntBinary(long num);
 * Description: Prints out number in binary format by printing 1 if bit is set
 *		or 0 if the bit if 0. The total number of bits is 32 since
 *		it is a long int. After every 4 bits space is printed
 * Paramters: 
 *	arg1: long num -- number that we need to print the binary numbers of
 * Side Effects: Masking bit while keeping track of counter
 * Error Conditions: None 
 * Return Value: None
 * Registers Used:
 *	%i0 - arg 1 -- int array that contains 2 indexes
 *	%l0 -- counter that tracks when to switch to next index of array
 *	%l1 -- original int that stays unchanged throughout program
 *	%l2 -- value of bitmask is stored here
 *	%l3 -- shifted left logical value (int)
 *	%l4 -- result (int) after bitmasking
 *	%l5 -- flag set to switch to second index
 */

printIntBinary:
 	
	save	%sp, -96, %sp		!Save caller's window

	clr	%l2			!clear local registers so we have their
	clr	%l0			!intial value set to 0. 
	clr	%l1
	clr	%l5

	set	BITMASK, %l2		!store bitmask hex inside local reg

	mov	%i0, %l1
	mov	%l1, %l3

LoopOver:
	and	%l3,%l2 , %l4		!Bitmask first index with bitwise &
					!operator to extract MSB
	cmp	%l4, %l2		!compare if result is equal to value
	be	One			!of bitmask, if it is, then print
	nop				!'0'

	set	fmt, %o0
	mov	0 , %o1
	call	printf
	nop

PartOfLoop:
	inc	%l0			!increment counter to see when to
					!switch to next index
	cmp	%l0, INTEGER_BIT	!if counter is still in bank 1,
	bl	CheckSpace		!then keeping looping to bitmask
	nop
	
	ba	Return			!Done with both 1st and 2nd index
	nop

CheckSpace:
	mov     %l0, %o0		!check if 4 bits have been printed
 	mov     FOUR, %o1		!if they have, then print space before
  	call    .rem			!printing next bit
	nop

	cmp     %o0, %g0		!print space after 4 bits
        be      Space
        nop

ShiftLeft:
	sll	%l3, 1, %l3		!shift left logical by 1 bit, then
	ba	LoopOver		!continue looping to & for bitmask
	nop

Space:
	set	nwLine, %o0
	mov	SPACE, %o1		!print space character between bits
	call	printf
	nop

	ba	ShiftLeft		!keep shifting int to the left
	nop
One:
	set	fmt, %o0
	mov	1 , %o1
	call	printf			!print '1' by using printf
	nop
	
	ba	PartOfLoop
	nop

Return:

	ret				!Return from subroutine
	restore				!Restore caller's window
