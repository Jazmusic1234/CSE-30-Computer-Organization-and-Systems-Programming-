/*
 * Filename: translate.s
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/4/2019
 * Sources of Help: writeup
 */

# Raspberry Pi derectives
	.cpu	cortex-a53
	.syntax	unified

	.equ	FP_OFFSET, 4

	.equ	PARAM_SPACE, 8
	.equ	PATTERN_OFFSET, -8 

	.section	.rodata

	.global	translate
	.text
	.align 2

/*
 * Function Name: translate()
 * Function Prototype: void translate( unsigned int pattern[], int hOffset, 
 *	int vOffset );
 * Description: Translate pattern horizontally by hOffset and vertically
 *	by vOffset
 * Parameters: pattern - array of bits that represents the 8x8 image
 *	       hOffset - how much to scroll horizontally
 *	       vOffset - how much to scroll vertically
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
translate:
	push	{fp, lr}
	add	fp, sp, FP_OFFSET

	sub	sp, sp, PARAM_SPACE		@ Allocate space on stack
	str	r0, [fp, PATTERN_OFFSET]	@ Store pattern on stack

	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	bl	scrollHorizontal		@ Scroll pattern horizontal by hOffset

	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	mov	r1, r2				@ Move vOffset to be 2nd arg
	bl	scrollVertical			@ Scroll pattern vertical by vOffset

epilogue:
	sub	sp, fp, FP_OFFSET

	pop	{fp, pc}
