/*
 * Filename: myRem.s
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/11/2019
 * Sources of Help: write up, notes #4, Week 2 Discussion Worksheet, 
 * 	piazza post #151 
 */

# Raspberry Pi directives
	.cpu	cortex-a53		@ Our Raspberry Pi
	.syntax	unified			@ Modern syntax

	.equ	FP_OFFSET, 4

	.section	.rodata		@ Need .section asm directive for .rodata

	.global	myRem
	.text
	.align	2

/*
 * Function Name: myRem()
 * Function Prototype: int myRem( int dividend, int divisor );
 * Description: Calculate remainder of dividend divided by divisor
 * Parameters: dividend - number to divide into
 	       divisor - number to divide by
 * Side Effects: None
 * Error Conditions: if divisor = 0, result in undefined
 * Return Value: remainder - number that is left over when dividend is divided
 * 	by divisor
 *
 * Registers used:
 * 	r0 - dividend and return value
 *	r1 - divisor
 * 	r2 - temporarily store remainder
 */
myRem:
	@ Prologue
	push	{fp, lr}		@ save caller's frame pointer (fp/r11) and
					@   return address (lr/r14) on the stack

	add	fp, sp, FP_OFFSET	@ set fp to point to base of saved regs

	sdiv 	r2, r0, r1		@ r2 = r0 / r1
	mul	r3, r2, r1		@ r3 = r2 / r1
	sub	r2, r0, r3		@ r2 = r0 - r3
	mov	r0, r2			@ move remainder from r2 to r0

	b 	epilogue

epilogue:
	sub	sp, fp, FP_OFFSET	@ set sp to top of save regs
					@   this also deallocates any local 
					@   vars and saved formal params
	
	pop	{fp, pc}		@ restore caller's frame pointer and
					@   pop return address (lr) into 
					@   pc which acts as return

