/*
 * Filename: printBase.s
 * Author: Gurkirat Singh
 * Description: This file prints the number inputted in the base given. It uses
 *		recursion to extract the least significant digit and 
 *		recursively print the number back in the base. It stops when 
 *		the number is only one digit long.
 */

		.global printBase	!global variable to call the function
					!from another file

		.section ".data"	!store the info below in data segment

INDEX_SHIFT = 4		!offset used to store num on stack

!used to print out one character of num
fmtChar:	.asciz "%c"

!index through this array to find the num to print
baseArray: .asciz "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" 
		
		.section ".text"	!text segment begins here

/* 
 * Function name: printBase()
 * Function prototype: void printBase (long num, int base);
 * Description: This function recursively calls itself to print the number
 *		given to us in the base provided. First find the right most
 *		number (LSD) and then recursively pass what is left of the
 *		quotient and stop when number is only 1 digit long.
 * Paramters: 
 *	arg 1 -- long num -- number that we need to print
 *	arg 2 -- int base -- base that we need to print the number in
 * Side effects: base case might be missed; prints character by character
 * Error conditions: None; error conditions happen in other c files
 * Return value: None
 * Registers used:
 *	%i0: number that was passed in
 *	%i1: base we need to print the number in
 *	%l0: copy of LSD that is stored on the stack
 *	%l1: array of strings
 *	%l3: LSD loaded from the stack
 *	%l4: remaining digits from recursion
 *	%l5: extract character from the char array defined above
 *	%l6: stores the copy of the base passed in
 */

printBase:
	save	%sp, -96, %sp		!Save caller's window

	clr	%l0			!clear all registers we are going
	clr	%l1			!to use
	clr	%l3
	clr 	%l4
	
	set	baseArray, %l1		!store the char array in local reg
	mov	%i1, %l6		!create a copy to use of the base num

	mov	%i0, %o0		!find the least significant digit
	mov	%l6, %o1		!by calling the modulus
	call	.rem
	nop
	
	mov	%o0, %l0		!copy the LSD in local reg
	st	%l0, [%fp - INDEX_SHIFT]!store LSD on stack for recursion
	
	mov	%i0, %o0		!get the left over numbers by 
	mov	%l6, %o1		!diving num with the base
	call	.div
	nop

	mov	%o0, %l4		!store result in local register

	cmp	%i0, %i1		!check if num is only 1 digit long
	bl	baseCaseHit		!this is our base case
	nop

	mov	%l4, %o0		!continue through recursion by
	mov	%l6, %o1		!calling the function
	call	printBase
	nop

baseCaseHit:
	ld	[%fp - INDEX_SHIFT],%l3 !load the LSD in local register 

	ldub	[%l1 + %l3],%l5		!contains character pointer
	set	fmtChar, %o0		!print the LSD one at a time
	mov	%l5, %o1
	call	printf
	nop
	
	ret				!return from the stack until it is
	restore				!all completed

