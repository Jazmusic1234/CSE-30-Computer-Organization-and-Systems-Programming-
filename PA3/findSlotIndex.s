/*
 * Filename: findSlotIndex.s
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/11/2019
 * Sources of Help: write up
 */

 	.cpu	cortex-a53	@ Our Raspberry Pi
	.syntax	unified		@ Modern syntax

	.equ	FP_OFFSET, 4
	
	// Formal parameters
	.equ	PARAM_SPACE, 8
	.equ	NUM_SLOTS, -8

	.section	.rodata	@ Need .section asm directive for .rodata

	.global	findSlotIndex
	.text
	.align	2

/*
 * Function Name: findSlotIndex()
 * Function Prototype: unsigned int findSlotIndex( const char * wordStr,
 *	size_t numSlots );
 * Description: Calculate index in slot array of size numSlots for given string
 * Parameters: wordStr - string to find index for
 *	       numSlots - size of slot array
 * Side Effects: None
 * Error Conditions: None
 * Return Value: index of wordStr in solt array
 *
 * Registers used:
 *	r0 - wordStr
 *	r1 - numSlots and temporarily store variables for calculations
 *	r2 - temporarily store variables for calculations
 *
 * Stack variables:
 *	numSlots - [fp - 8] - number of slots
 */
findSlotIndex:

	@ Prologue
	push	{fp, lr}		@ save caller's frame pointer

	add	fp, sp, FP_OFFSET	@ set fp to base of saved regs

	sub	sp, sp, PARAM_SPACE	@ Allocate param space
	str	r1, [fp, NUM_SLOTS]	@ Store numSlots on stack

	// Calculate hash value of wordStr
	bl	computeHash		@ Get hashValue of wordStr

	// Mod hash value by numSlots
	ldr	r1, [fp, NUM_SLOTS]	@ Load numSlots
	bl	myURem			@ hashValue % numSlots


epilogue:
	sub	sp, fp, FP_OFFSET
	
	pop	{fp, pc}
