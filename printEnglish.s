/*
 * Filename: printEnglish.s
 * Author: Gurkirat Singh
 * Description: This file takes in a num and then recursively prints each num
 *		as a word. It stores the LSD on the stack first and then 
 *		calls itself a number of times until the num is only 1 digit
 *		long and then prints out the word pertaining to it one at a
 *		time.
 */

		.global printEnglish	!Declare a global symbol to call file
					!from outside

		.section ".data"	!info below goes in data segment

LSDExtractor = 10		!extract the LSD from the num
DOUBLE_DIGIT = 10		!to check if num is only 1 digit long
INDEX_SHIFT = 4			!offset to use for storing on the stack
Space = ' '			!space to print between the words

zero:		.asciz "zero"
one:		.asciz "one"
two:		.asciz "two"
three:		.asciz "three"
four:		.asciz "four"
five:		.asciz "five"
six:		.asciz "six"
seven:		.asciz "seven"
eight:		.asciz "eight"
nine:		.asciz "nine"

fmtString:	.asciz "%s"
fmtChar:	.asciz "%c"

		.align 4!	!align each char on 4 bytes

!array of char pointers
engArray: .word zero,one,two,three,four,five,six,seven,eight,nine

		.section ".text"!text section begins here

/* 
 * Function name: printEnglish()
 * Function prototype: void printEnglish (long num);
 * Description: This function extracts the LSD from the number in base 10
 *		and then recursively calls itself untli the num is 1 digit
 *		long, each time storing the LSD on the stack. Then it prints
 *		out each character in a word form by finding index from 
 *		char pointer array.
 * Paramters:
 *	arg 1: long num -- number to print in words
 * Side effects: prints out each character one at a time
 * Error conditions: None. Conditions are handled in c files
 * Return value: None
 * Registers used:
 *	%l0: copy of LSD that is stored on the stack
 *	%l1: array of char pointers (strings)
 *	%l3: stores the LSD loading from the stack
 *	%l4: remaining digits that still need to be called recursively 
 *	%l5: contains char pointer of the word we need to print out
 */

printEnglish:
	save	%sp, -96, %sp		!save caller's window

	clr	%l0			!clear all local registers
	clr	%l1			!that are going to be used
	clr	%l3
	clr 	%l4

	set	engArray, %l1		!store the char pointer array
					!in a local var for further use

	mov	%i0, %o0		!find out the LSD from the num
	mov	LSDExtractor, %o1	!using the modulus
	call	.rem
	nop
	
	mov	%o0, %l0		!store the result in local reg
	st	%l0, [%fp - INDEX_SHIFT]!store the LSD on the stack
	
	mov	%i0, %o0		!find the remaining digits that still
	mov	LSDExtractor, %o1	!need to be called recursively
	call	.div
	nop

	mov	%o0, %l4		!store the remaining digits in local
					!register

	cmp	%i0, DOUBLE_DIGIT	!check if we have hit the base case yet
	bl	baseCaseHit
	nop

	mov	%l4, %o0		!base case is not hit, continue with
	call	printEnglish		!recursion
	nop

baseCaseHit:
	ld	[%fp - INDEX_SHIFT], %l3!load the LSD into local variable
	mov	%l3, %o0		!using 4 bytes offset, find word for 
	mov	INDEX_SHIFT, %o1	!given number
	call	.mul
	nop

	ld	[%l1 + %o0],%l5		!contains character pointer
	set	fmtString, %o0		!print the word out 
	mov	%l5, %o1
	call	printf
	nop
	
	set 	fmtChar, %o0		!print space between words
	mov	Space, %o1
	call	printf
	nop

	ret				!deallocate stack until all are gone
	restore

