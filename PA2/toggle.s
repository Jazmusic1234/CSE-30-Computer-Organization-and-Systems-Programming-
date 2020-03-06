/*
 * Filename: toggle.s
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 4/25/2019
 * Sources of Help: writeup, Week 4 Discussion Worksheet
 */

# Raspberry Pi derectives
	.cpu	cortex-a53
	.syntax	unified

	.equ	FP_OFFSET, 4

	.equ	PARAM_OFFSET, 16
	.equ	PART0_OFFSET, -8
	.equ	PART1_OFFSET, -12
	.equ	PATTERN_1_OFFSET, 4

	.section	.rodata

	.global	toggle
	.text
	.align 2

/*
 * Function Name: toggle()
 * Function Prototype: void toggle( unsigned int pattern[], 
 *	unsigned int part0, unsigned int part1 );
 * Description: Toggles bit in pattern if part0 or part1 bit is 1, else
 *	stays same
 * Parameters: pattern -array of bits that represents the 8x8 image
 *		part0 - user input which determines the 1st 4 lines of image
 *		part1 - user input which determines the last 4 lines of image
 *
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *	r0 - 1st arg
 *	r1 - 2nd arg and temporarily store values for calculations
 *	r2 - 3rd arg and temporarily store values for calculations
 *	r3 - temporarily store values for calculations
 */
toggle:
	push	{fp, lr}
	add	fp, sp, FP_OFFSET

	sub	sp, sp, PARAM_OFFSET		@ Allocate param space on stack

	str	r1, [fp, PART0_OFFSET]		@ Store part0 on stack
	str	r2, [fp, PART1_OFFSET]		@ Store part1 on stack

	ldr	r1, [r0]			@ Load pattern[0]
	ldr	r2, [fp, PART0_OFFSET]		@ Load part0
	eor	r3, r1, r2			@ r3 = pattern[0] XOR part0
	str	r3, [r0]			@ Store pattern[0]

	ldr	r1, [r0, PATTERN_1_OFFSET]	@ Load pattern[1]
	ldr	r2, [fp, PART1_OFFSET]		@ Load part1
	eor	r3, r1, r2			@ r3 = pattern[1] XOR part1
	str	r3, [r0, PATTERN_1_OFFSET]	@ Store pattern[1]

epilogue:
	sub	sp, fp, FP_OFFSET

	pop	{fp, pc}
