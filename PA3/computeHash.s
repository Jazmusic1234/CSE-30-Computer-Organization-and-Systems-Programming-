/*
 * Filename: computeHash.s
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/11/2019
 * Sources of Help: write up, Week 6 Discussion Worksheet
 */

 	.cpu	cortex-a53	@ Our Raspberry Pi
	.syntax	unified		@ Modern syntax

	.equ	FP_OFFSET, 4

	// Local variables
	.equ	LOCAL_SPACE, 8
	.equ	HASH_OFFSET, -8
	.equ	I_OFFSET, -12

	.section	.rodata	@ Need .section asm directive for .rodata

	.global	computeHash
	.text
	.align	2

/*
 * Function Name: computeHash()
 * Function Prototype: unsigned int computeHash( const char * str );
 * Description: generate hash value of a given string
 * Parameters: str - string to create hashValue for
 * Side Effects: None
 * Error Conditions: None
 * Return Value: hash value of str
 *
 * Registers used:
 *	r0 - str - string to create hashValue for
 *	r1 - temporarily store variables for calculations
 *	r2 - temporarily store variables for calculations
 *	r3 - temporarily store variables for calculations
 * 
 * Stack variables:
 *	hash - [f - 8] - hashValue of str
 *	i - [f - 12] - for loop increment
 */
computeHash:

	@ Prologue
	push	{fp, lr}			@ save caller's frame point

	add	fp, sp, FP_OFFSET		@ set fp to base of saved regs

	// Store local vars
	sub	sp, sp, LOCAL_SPACE		@ Allocate local var space
	ldr	r2, =G_HASH_START_VAL		@ Load address of HASH_START_VAL
	ldr	r2, [r2]			@ Load HASH_START_VAL
	str	r2, [fp, HASH_OFFSET]		@ Store hash
	mov	r3, 0				@ r3 = 0
	str	r3, [fp, I_OFFSET]		@ Store i

	// Check negative logic
	ldr	r3, [fp, I_OFFSET]		@ Load i
	ldrb	r1, [r0, r3]			@ Load str[i]
	cmp	r1, 0				@ Compare r1 and 0
	beq	epilogue			@ if str[i] = '\0', end loop

	// for loop
loop:
	ldr	r2, [fp, HASH_OFFSET]		@ Load hash
	ldr	r1, =G_HASH_PRIME		@ Load address of HASH_PRIME
	ldr	r1, [r1]			@ Load HASH_PRIME
	mul	r2, r2, r1			@ hash * HASH_PRIME
	ldr	r3, [fp, I_OFFSET]		@ Load i
	ldrb	r1, [r0, r3]			@ Load str[i]
	add	r2, r2, r1			@ hash = hash*HASH_PRIME+str[i]		
	str	r2, [fp, HASH_OFFSET]		@ Store hash

	// Increment i
	ldr	r3, [fp, I_OFFSET]		@ Load i
	add	r3, r3, 1			@ i = i + 1
	str	r3, [fp, I_OFFSET]		@ Store i

	// Check positive logic
	ldr	r3, [fp, I_OFFSET]		@ Load i
	ldrb	r1, [r0, r3]			@ Load str[i]
	cmp	r1, 0				@ Compare r1 and 0
	bne	loop				@ if str[i] != '\0', loop again

epilogue:
	// Once for loop ends, return hash
	ldr	r0, [fp, HASH_OFFSET]		@ return hash
	
	sub	sp, fp, FP_OFFSET
	
	pop	{fp, pc}
