/*
 * Filename: myURem.s
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/11/2019
 * Sources of Help: write up, Week 6 Discussion Worksheet
 */

 	.cpu	cortex-a53	@ Our Raspberry Pi
	.syntax	unified		@ Modern syntax

	.equ	FP_OFFSET, 4

	.section	.rodata	@ Need .section asm directive for .rodata

	.global	myURem
	.text
	.align	2

/*
 * Function Name: myURem()
 * Function Prototype: unsigned int myURem( unsigned int dividend, 
 *	unsigned int divisor );
 * Description: Calculate remainder when dividend, divisor, and remainder
 *	are all unsigned integers
 * Parameters: dividend - unsigned int to divide into
 *	       divisor - unsigned int to divide by
 * Side Effects: None
 * Error Conditions: if divisor is 0, result is undefined
 * Return Value: The remainder
 *
 * Registers used:
 *	r0 - dividend
 *	r1 - divisor
 *	r2 - temporarily store variables for calculations
 */
myURem:

	@ Prologue
	push	{fp, lr}		@ save caller's frame pointer 

	add	fp, sp, FP_OFFSET	@ set fp to point to base of saved regs

	udiv	r2, r0, r1		@ r2 = r0 / r1
	mul	r3, r2, r1		@ r3 = r2 * r1
	sub	r0, r0, r3		@ r2 = r0 - r3

epilogue:
	sub	sp, fp, FP_OFFSET
	
	pop	{fp, pc}
