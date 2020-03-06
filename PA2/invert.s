/*
 * Filename: invert.s
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/3/2019
 * Sources of Help: writeup
 */

# Raspberry Pi derectives
	.cpu	cortex-a53
	.syntax	unified

	.equ	FP_OFFSET, 4

	.equ	INVERT_ALL, 0xFFFFFFFF	

	.section	.rodata

	.global	invert
	.text
	.align 2

/*
 * Function Name: invert()
 * Function Prototype: void invert( unsigned int pattern[] );
 * Description: Inverts all bits in pattern
 * Parameters: pattern - array of bits that represents the 8x8 image
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *	r0 - 1st arg
 *	r1 - temporarily store values for calculations
 *	r2 - temporarily store values for calculations
 *	r3 - temporarily store values for calculations
 */
invert:
	push	{fp, lr}
	add	fp, sp, FP_OFFSET

	mov	r1, INVERT_ALL			@ Load 0xFFFFFFFF into r1
	mov	r2, INVERT_ALL			@ Load 0xFFFFFFFF into r2
	bl	toggle				@ Toggle all bits

epilogue:
	sub	sp, fp, FP_OFFSET

	pop	{fp, pc}
