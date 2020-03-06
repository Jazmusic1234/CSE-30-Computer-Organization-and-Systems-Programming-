/*
 * Filename: outputChar.s
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/11/2019
 * Sources of Help: write up, notes #4, Week 2 Discussion Worksheet,
 * 	piazza post #151, #147
 */

	.cpu	cortex-a53
	.syntax	unified

	.equ	FP_OFFSET, 4

	.section	.rodata

fmt:
	.asciz	"%c"

	.global	outputChar
	
	.text
	.align	2

/*
 * Function Name: outputChar()
 * Function Prototype: void outputChar( char ch );
 * Description: prints the given screen to stdout
 * Parameters: ch - character to be printed
 * Side Effects: prints to stdout
 * Error Conditions: None
 * Return Value: None
 *
 * Registers used:
 *	r0 - ch
 */
 outputChar:
	push	{fp, lr}

	add	fp, sp, FP_OFFSET

	mov	r1, r0
	ldr	r0, =fmt
	bl	printf

	sub	sp, fp, FP_OFFSET

	pop	{fp, pc}
