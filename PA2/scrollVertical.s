/*
 * Filename: scrollVertical.s
 * Author: Jasmine Chen 
 * UserId: cs30xax
 * Date: 4/25/2019
 * Sources of Help: writeup
 */

# Raspberry Pi derectives
	.cpu	cortex-a53
	.syntax	unified

	.equ	FP_OFFSET, 4

	.equ	LOCAL_SPACE, 8
	.equ	END_OFFSET, -8

	.equ	PARAM_OFFSET, 24
	.equ	PATTERN_OFFSET, -16
	.equ	OFFSET_OFFSET, -20
	.equ	PATTERN1_OFFSET, 4

	.equ	MSB_MASK, 0xFF000000
	.equ	LSB_MASK, 0x000000FF

	.section	.rodata

	.global	scrollVertical
	.text
	.align 2

/*
 * Function Name: scrollVertical()
 * Function Prototype: void scrollVertical( unsigned int pattern[], 
 *	int offset );
 * Description: Scroll pattern vertically by given offset
 * Parameters: pattern - array of bits that represents the 8x8 image 
 *	       offset - how much to scroll up or down by
 *
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *	r0 - 1st arg
 *	r1 - 2nd arg
 *	r2 - temporary storage for calculations
 *	r3 - temporary storage for calculations
 */
scrollVertical:
	push	{fp, lr}
	add	fp, sp, FP_OFFSET

	sub	sp, sp, LOCAL_SPACE		@ Allocate local var space

	sub	sp, sp, PARAM_OFFSET		@ Allocate param space
	str	r0, [fp, PATTERN_OFFSET]	@ Store pattern
	str	r1, [fp, OFFSET_OFFSET]		@ Store offset

	ldr	r1, [fp, OFFSET_OFFSET]		@ Load offset
	cmp	r1, 0
	bgt	scroll_down			@ If offset pos, scroll down
	
	ldr	r1, [fp, OFFSET_OFFSET]		@ Load offset
	cmp	r1, 0
	blt	scroll_up			@ If offset neg, scroll up

	b	epilogue

scroll_down:
	@ Shift LSB of pattern[1] left
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	ldr	r1, [r0, PATTERN1_OFFSET]	@ Load pattern[1]
	and	r2, r1, LSB_MASK		@ Get LSB 	
	lsl	r3, r2, 24			@ Shift r2 left by 24 bits
	str	r3, [fp, END_OFFSET]		@ Store end byte

	@ Get LSB of pattern[0]
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	ldr	r3, [r0]			@ Load pattern[0]
	and	r1, r3, LSB_MASK		@ Get LSB
	lsl	r2, r1, 24			@ Shift r1 left by 24 bits

	@ Move LSB of pattern[0] to MSB of pattern[1]
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	ldr	r1, [r0, PATTERN1_OFFSET]	@ Load pattern[1]
	lsr	r3, r1, 8			@ Shift pattern[1] right by 8
	orr	r3, r2, r3			@ Combine r2 and r3
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	str	r3, [r0, PATTERN1_OFFSET]	@ Store new pattern[1]

	@ Shift pattern[0] right by 1 byte
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	ldr	r3, [r0]			@ Load pattern[0]
	lsr	r1, r3, 8			@ Shift r0 right by 8 bits

	@ Move LSB of pattern[1] to MSB of pattern[0]
	ldr	r2, [fp, END_OFFSET]		@ Load end byte
	orr	r3, r2, r1			@ Combine r2 and r1
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load new pattern[0]
	str	r3, [r0]			@ Store pattern[0]

	@ Increment
	ldr	r1, [fp, OFFSET_OFFSET]		@ Load offset
	sub	r1, r1, 1			@ Offset - 1
	str	r1, [fp, OFFSET_OFFSET]		@ Store offset
	ldr	r1, [fp, OFFSET_OFFSET]		@ Load offset
	cmp	r1, 0				
	bgt	scroll_down			@ if offset > 0, loop again

	b	epilogue

scroll_up:
	@ Shift MSB of pattern[0] right
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	ldr	r3, [r0]			@ Load pattern[0]
	and 	r1, r3, MSB_MASK		@ Get MSB
	lsr	r2, r1, 24			@ Shift r1 right by 24 bits
	str	r2, [fp, END_OFFSET]		@ Store end byte

	@ Get MSB of pattern[1]
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	ldr	r1, [r0, PATTERN1_OFFSET]	@ Load pattern[1]
	and	r2, r1, MSB_MASK		@ Get MSB
	lsr	r3, r2, 24			@ Shift r2 right by 24 bits

	@ Move MSB of pattern[1] to LSB of pattern[0]
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	ldr	r2, [r0]			@ Load pattern[0]
	lsl	r2, 8				@ Shift r0 left by 8 bits
	orr	r1, r2, r3			@ Combine r0 and r3
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	str	r1, [r0]			@ Store new pattern[0]

	@ Shift pattern[1] left by 1 byte
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	ldr	r1, [r0, PATTERN1_OFFSET]	@ Load pattern[1]
	lsl	r2, r1, 8			@ Shift r1 left by 8 bits

	@ Move MSB of pattern[0] to LSB of pattern [1]
	ldr	r1, [fp, END_OFFSET]		@ Load end byte
	orr	r3, r1, r2			@ Combine r1 and r2
	ldr	r0, [fp, PATTERN_OFFSET]	@ Load pattern
	str	r3, [r0, PATTERN1_OFFSET]	@ Store new pattern[1]

	@ Increment
	ldr	r1, [fp, OFFSET_OFFSET]		@ Load offset
	add	r1, r1, 1			@ Offset + 1
	str	r1, [fp, OFFSET_OFFSET]		@ Store offset
	ldr	r1, [fp, OFFSET_OFFSET]		@ Load offset
	cmp	r1, 0
	blt	scroll_up			@ if offset < 0, loop again

epilogue:
	sub	sp, fp, FP_OFFSET

	pop	{fp, pc}
