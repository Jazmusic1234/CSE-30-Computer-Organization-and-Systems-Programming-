/*
 * Filename: intervalContains.s
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/11/2019
 * Sources of Help: write up, notes $4, Week 2 Discussion Worksheet,
 * 	piazza post #151, #147
 */

 	.cpu	cortex-a53		@ Our Raspberry Pi
	.syntax	unified			@ Modern syntax

	.equ	FP_OFFSET, 4

	.section	.rodata		@ Need .section asm directive for .rodata

	.global	intervalContains
	.text
	.align	2


/*
 * Function Name: intervalContains()
 * Function Prototype: int intervalContains( int start, int end, int value );
 * Description: checks that given value is between start and end inclusive
 * Parameters: start - lower bound
 *	       end - upper bound
 *	       value - given value
 * Side Effects: None
 * Error Conditions: if start > end, return -1
 * Return Value: if error, return -1
 * 		 if value is between start and end, return 1
 * 		 if value is not between start and end, return 0
 *
 * Registers used:
 *	r0 - start and return value
 *	r1 - end
 *	r2 - value
 */
intervalContains:

	@ Prologue
	push	{fp, lr}

	add	fp, sp, FP_OFFSET

	cmp	r0, r1
	bgt	error

	cmp	r2, r0
	blt	else

	cmp	r2, r1
	bgt	else

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
