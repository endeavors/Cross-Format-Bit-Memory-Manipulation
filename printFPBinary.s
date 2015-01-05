/*
 * Filename: printIntBinary.s
 * Author: Gurkirat Singh
 * Description: This file has a paramter of long num and it prints out
 *		the standard binary representation of the number, however,
 *		the bits are separated in 3 sections:sign bit, exponent bits,
 *		and the mantissa bits.
 */

BITMASK = 0x80000000		!bitmask of 1 to get most significant bit		
NEWLINE = '\n'
SPACE = ' '
FOUR = 4
INTEGER_BIT = 32		!counter to keep track when to switch to next
				!index
SIGN_BIT = 1			!number of bits for sign bit
EXP_BIT = 9			!number of bits for exponent bits

 	.global printFPBinary	!Declare global variable so we can call it from
				!another file
	.section ".data"

fmt:	.asciz "%d"
nwLine:	.asciz "%c"

	.section ".text"	!The text segment begins here

/*
 * Function: printFPBinary(float fpnum)
 * Function prototype: void printFPBinary(float fpnum)
 * Description: Print out the binary representation of the number and 
 *		dividing how the bits are printed out in 3 sections. 1 bit
 *		for sign bit, 8 bits for exponent, and 23 for mantissa bits
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

printFPBinary:
 	
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
					!how many bits have been printed
	cmp	%l0, SIGN_BIT
	be	Space
	nop

	cmp	%l0, EXP_BIT		!print space after exponent bits (9)
	be	Space
	nop
	
					!switch to next index
	cmp	%l0, INTEGER_BIT	!if counter is still in bank 1,
	bl	ShiftLeft		!then keeping looping to bitmask
	nop
	
	ba	Return			!Done with both 1st and 2nd index
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
	call	printf			!'1' by using printf
	nop
	
	ba	PartOfLoop
	nop

Return:
	set	nwLine, %o0
	mov	NEWLINE, %o1		!print newline after we are done with
	call	printf			!printing light on/off
	nop

	ret				!Return from subroutine
	restore				!Restore caller's window
