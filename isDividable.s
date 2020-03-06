/*
 * Filename: isDividable.s
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/11/2019
 * Sources of Help: write up, notes #4, Week 2 Discussion Worksheet, 
 * 	piazza post #151. #147
 */

	.cpu	cortex-a53		@ Our Raspberry Pi
	.syntax	unified			@ Modern syntax

	.equ	FP_OFFSET, 4

	.section	.rodata		@ Need .section asm directive for .rodata

	.global	isDividable
	.text
	.align	2


/*
 * Function Name: isDividable()
 * Function Prototype: int isDividable( int dividend, int divisor );
 * Description: check whether dividend is evenly dividable by the divisor
 * Parameters: dividend - number to be divided into
 	       divisor - number to be divided by
 * Side Effects: None
 * Error Conditions: if divisor = 0, return -1
 * Return Value: if error, return -1
 * 		 if dividable, return 1
 * 		 if not dividable, return 0
 *
 * Registers used:
 * 	r0 - dividend and return value
 *	r1 - divisor
 */

isDividable:
	@ Prologue
	push	{fp, lr}		

	add	fp, sp, FP_OFFSET

	cmp	r1, 0
	beq	error

	bl	myRem			@ branch and link

	cmp	r0, 0
	bne	else

	mov	r0, 1
	
	b	epilogue

error:
	mov	r0, -1
	b	epilogue

else:
	mov	r0, 0
	
epilogue:
	sub	sp, fp, FP_OFFSET

	pop	{fp, pc}
