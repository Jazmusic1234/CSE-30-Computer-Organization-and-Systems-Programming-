/*
 * Filename: lineMatchesRegex.s
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/25/2019
 * Sources of Help: write up, bob.cs.sonoma.edu
 */

	.cpu	cortex-a53		@ Our Raspberry Pi
	.syntax	unified			@ Modern syntax

	.equ	FP_OFFSET, 4

	.equ	ARG_SPACE, 8

	.section	.rodata		@ Need .section asm directive for .rodata

	.global	lineMatchesRegex
	.text
	.align	2

/*
 * Function Name: lineMatchesRegex()
 * Function Prototype: int lineMatchesRegex( const regex_t * pattern, 
 *	const char * line );
 * Description: Check if line matches regex pattern 
 * Parameters: pattern - regex pattern to check for match with
 	       line - line of words to check if it match pattern
 * Side Effects: None
 * Error Conditions: None 
 * Return Value: if line matches pattern, return 1
 *		 if line doesn not match pattern, return 0
 * 
 * Registers used:
 * 	r0 - pattern 
 *	r1 - line
 * 	r2 - third arg of regexec
 *	r3 - fourth arg of regexec and temp for storing on stack
 *
 * Stack variables:
 *	arg5 - [sp] - fifth arg for regexec
 */

lineMatchesRegex:
	
	@ Prologue
	push	{fp, lr}		@ Save caller's frame pointer

	add	fp, sp, FP_OFFSET	@ Set fp to base of saved regs

	sub	sp, sp, ARG_SPACE	@ Allocate param space
	
	mov 	r3, 0			@ r3 = 0
	str	r3, [sp]		@ Store fifth arg on stack
	mov	r2, 0			@ third arg = 0
	mov	r3, 0			@ fourth arg = 0

	bl	regexec			@ regexec( pattern, line, 0, 0, 0 )

	cmp	r0, 0			
	beq	match			@ if regexec returns 0 ( matches)
	
	mov	r0, 0			@ if doesn't match, return 0
	b	epilogue

match: 
	mov	r0, 1			@ if match, return 1
	
epilogue:
	sub	sp, fp, FP_OFFSET

	pop	{fp, pc}
