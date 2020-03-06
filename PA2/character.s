/*
 * Filename: character.s
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 4/25/2019
 * Sources of Help: writeup, piazza
 */

# Raspberry Pi derectives
	.cpu	cortex-a53
	.syntax	unified

	.equ	FP_OFFSET, 4

	.equ	PARAM_OFFSET, 16
	.equ	PATTERN_OFFSET, -8
	.equ	CHAR_OFFSET, -12
	.equ	ALPHA_OFFSET, -16
	.equ	NUM_OFFSET, -20

	.equ	ASCII_LETTER_START, 65
	.equ	ASCII_LETTER_END, 90
	.equ	ASCII_DIGIT_START, 48
	.equ	ASCII_DIGIT_END, 57

	.equ	INT_SIZE, 4
	.equ	POINTER_SIZE, 4

	.section	.rodata

	.global	character
	.text
	.align 2

/*
 * Function Name: character()
 * Function Prototype: int character( unsigned int pattern[], char ch, 
 *	const char * alphabetPatterns[], const char * digitPatterns[] );
 * Description: Fill pattern with bit pattern of ch
 * Parameters: pattern - array of bits that represents the 8x8 image
 *	       ch - character to draw image of
 *	       alphabetPatterns - if ch is letter, search for its bit pattern
 *			in this array
 *	       digitPatterns - if ch is number, search for its bit pattern
 *			in the array
 *
 * Side Effects: None
 * Error Conditions: if ch is not letter or number, return -1
 * Return Value: if error, return -1
 *		  else, return 0
 * 
 * Registers used:
 *	r0 - 1st arg
 *	r1 - 2nd arg
 *	r2 - 3rd arg
 *	r3 - 4th arg
 */
character:
	push	{fp, lr}
	add	fp, sp, FP_OFFSET

	sub	sp, sp, PARAM_OFFSET	@ Allocate space on stack
	str	r0, [fp, PATTERN_OFFSET]@ Store pattern on stack
	str	r1, [fp, CHAR_OFFSET]	@ Store ch on stack
	str	r2, [fp, ALPHA_OFFSET]	@ Store alphaPatterns on stack 
	str	r3, [fp, NUM_OFFSET]	@ Store digitPatterns on stack

	@ Check that ch is letter
	ldr	r0, [fp, CHAR_OFFSET]
	bl	toupper				@ Make uppercase
	str	r0, [fp, CHAR_OFFSET]		@ Store uppercase ch
	ldr	r2, [fp, CHAR_OFFSET]		@ Load ch
	mov	r0, ASCII_LETTER_START  
	mov	r1, ASCII_LETTER_END
	bl	intervalContains		@ intervalContains(r0, r1, r2)
	cmp	r0, 1
	beq	alpha_loop			@ If ch is letter

	@ Check that ch is digit
	ldr	r2, [fp, CHAR_OFFSET]
	mov	r0, ASCII_DIGIT_START  
	mov	r1, ASCII_DIGIT_END
	bl	intervalContains		@ intervalContains(r0, r1, r2)
	cmp	r0, 1
	beq	digit_loop

	mov 	r0, -1
	b	epilogue

alpha_loop:
	ldr	r3, [fp, CHAR_OFFSET]		@ Load ch
	sub	r3, r3, ASCII_LETTER_START	@ r3 = ascii value - 65
	mov	r0, POINTER_SIZE
	mul	r3, r3, r0			@ pointer = 4 bytes 
	ldr	r2, [fp, ALPHA_OFFSET]		@ Load alphaPatterns
	ldr	r1, [r2, r3]			@ Get bit pattern for ch
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	bl	loadPatternString		@ loadPatternString(r0, r1)
	mov	r0, 0				@ return 0
	b	epilogue

digit_loop:
	ldr	r3, [fp, CHAR_OFFSET]
	sub	r3, r3, ASCII_DIGIT_START	@ r3 = ascii value - 48 
	mov	r0, INT_SIZE
	mul	r3, r3, r0			@ int = 4 bytes 
	ldr	r2, [fp, NUM_OFFSET]		@ Load digitPatterns
	ldr	r1, [r2, r3]			@ Get bit pattern for ch
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	bl	loadPatternString		@ loadPatternString(r0, r1)
	
	mov	r0, 0				@ return 0

epilogue:
	sub	sp, fp, FP_OFFSET

	pop	{fp, pc}
