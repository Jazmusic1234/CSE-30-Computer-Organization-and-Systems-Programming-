/*
 * Filename: printPattern.s
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 5/4/2019
 * Sources of Help: writeup, Week 2 Discussion Worksheet
 */

# Raspberry Pi derectives
	.cpu	cortex-a53
	.syntax	unified

	.equ	FP_OFFSET, 4

	.equ	LOCAL_SPACE, 16
	.equ	I_OFFSET, -8
	.equ	BIT_OFFSET, -12
	.equ	PATTERN_NUM, -16

	.equ	PARAM_SPACE, 16
	.equ	PATTERN_OFFSET, -24
	.equ	CHAR_ON_OFFSET, -28
	.equ	CHAR_OFF_OFFSET, -32

	.equ	PATTERN1_OFFSET, 4
	
	.equ	INT_BITWIDTH, 32
	.equ	PATTERN_BITWIDTH, 8
	.equ	NEWLINE_CHAR, '\n'

	.section	.rodata

	.global	printPattern
	.text
	.align 2

/*
 * Function Name: printPattern()
 * Function Prototype: void printPattern( unsigned int pattern[], char on, char off );
 * Description: Print pattern as an 8x8 grid
 * Parameters: pattern - array of bits that represents the 8x8 image
 *	       on - character to represent 1/on bit
 *	       off - character to represent 0/off bit
 * Side Effects: Prints to stdout
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *	r0 - 1st arg
 *	r1 - 2nd arg and temporarily store values for calculations
 *	r2 - 3rd arg and temporarily store values for calculations
 *	r3 - temporarily store values for calculations
 */
printPattern:
	push	{fp, lr}
	add	fp, sp, FP_OFFSET

	sub	sp, sp, LOCAL_SPACE		@ Allocate local space

	sub	sp, sp, PARAM_SPACE		@ Allocate param space
	str	r0, [fp, PATTERN_OFFSET]	@ Store pattern on stack
	str	r1, [fp, CHAR_ON_OFFSET]	@ Store on char on stack
	str	r2, [fp, CHAR_OFF_OFFSET]	@ Store off char on stack
	
	mov	r1, INT_BITWIDTH		@ r1 = 32
	str	r1, [fp, I_OFFSET]		@ Store i
	
	mov	r1, 0				@ r1 = 0
	str	r1, [fp, PATTERN_NUM]		@ Store pattern num

print_pattern0:
	ldr	r0, [fp, I_OFFSET]		@ Load i
	sub	r0, r0, 1			@ i--
	str	r0, [fp, I_OFFSET]		@ Store i
	ldr	r1, [fp, PATTERN_OFFSET]	@ Load pattern
	ldr	r2, [r1]			@ Load pattern[0]
	lsr	r3, r2, r0			@ pattern[0] >> i
	and	r0, r3, 1			@ Get single bit
	str	r0, [fp, BIT_OFFSET]		@ Store bit

	ldr	r1, [fp, BIT_OFFSET]		@ Load bit
	cmp	r1, 1
	beq	print_on			@ if bit = 1, print on char

	cmp	r1, 0
	beq	print_off			@ if bit = 0, print off char
	
check0:
	ldr	r0, [fp, I_OFFSET]		@ Load i
	cmp	r0, 0				
	beq	end_loop			@ if pattern[0] done, pattern[1]

	ldr	r0, [fp, I_OFFSET]		@ Load i
	mov	r1, PATTERN_BITWIDTH		@ r1 = 8
	bl	myRem				@ myRem(i, 8)
	cmp	r0, 0
	bne	print_pattern0			@ if not end of byte, loop

	mov	r0, NEWLINE_CHAR		@ r0 = NEWLINE_CHAR
	bl	outputChar			@ outputChar('\n')
	b	print_pattern0			@ Loop again

check1:
	ldr	r0, [fp, I_OFFSET]		@ Load i
	cmp	r0, 0				
	beq	epilogue			@ if pattern[0] done, pattern[1]

	ldr	r0, [fp, I_OFFSET]		@ Load i
	mov	r1, PATTERN_BITWIDTH		@ r1 = 8
	bl	myRem				@ myRem(i, 8)
	cmp	r0, 0
	bne	print_pattern1			@ if not end of byte, loop

	mov	r0, NEWLINE_CHAR		@ r0 = NEWLINE_CHAR
	bl	outputChar			@ outputChar('\n')
	b	print_pattern1			@ Loop again

print_on:
	ldr	r0, [fp, CHAR_ON_OFFSET]	@ Load on char	
	bl	outputChar			@ if bit = 1, outputChar(on)
	ldr	r1, [fp, PATTERN_NUM]		@ Load pattern num
	cmp	r1, 0
	beq	check0				@ if pattern0, check0 branch
	cmp 	r1, 1
	beq	check1				@ if pattern1, check1 branch

print_off:
	ldr	r0, [fp, CHAR_OFF_OFFSET]	@ Load off char
	bl	outputChar			@ if bit = 1, outputChar(on)
	ldr	r1, [fp, PATTERN_NUM]		@ Load pattern num
	cmp	r1, 0
	beq	check0				@ if pattern0, check0 branch
	cmp 	r1, 1
	beq	check1				@ if pattern1, check1 branch

end_loop:
	mov	r0, NEWLINE_CHAR		@ r0 = NEWLINE_CHAR
	bl	outputChar			@ outputChar('\n')

	mov	r1, INT_BITWIDTH		@ r1 = 32
	str	r1, [fp, I_OFFSET]		@ Store i

	mov	r1, 1				@ r1 = 1
	str	r1, [fp, PATTERN_NUM]		@ Store pattern num
	
print_pattern1:
	ldr	r0, [fp, I_OFFSET]		@ Load i
	sub	r1, r0, 1			@ i--
	str	r1, [fp, I_OFFSET]		@ Store i
	ldr	r0, [fp, I_OFFSET]		@ Load i
	ldr	r1, [fp, PATTERN_OFFSET]	@ Load pattern
	ldr	r2, [r1, PATTERN1_OFFSET]	@ Load pattern[1]
	lsr	r3, r2, r0			@ pattern[0] >> i
	and	r0, r3, 1			@ Get single bit
	str	r0, [fp, BIT_OFFSET]		@ Store bit

	ldr	r1, [fp, BIT_OFFSET]		@ Load bit
	cmp	r1, 1
	beq	print_on			@ if bit = 1, print on char
	
	cmp	r1, 0
	beq	print_off			@ if bit = 0, print off char

epilogue:
	mov	r0, NEWLINE_CHAR		@ r0 = NEWLINE_CHAR
	bl	outputChar			@ outputChar('\n')

	sub	sp, fp, FP_OFFSET

	pop	{fp, pc}
