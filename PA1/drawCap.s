/*
 * Filename: drawCap.s
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 4/19/2019
 * Sources of Help: write up, notes #4, Week 2 Discussion Worksheet, 
 * piazza post #417
 */

 #Raspberry Pi derectives
 	.cpu	cortex-a53		@ Our Raspberry PI
	.syntax	unified			@ Modern syntax

	.equ	FP_OFFSET, 4

	.section	.rodata		@ Need .section asm directive for .rodata

	.global	drawCap
	.text
	.align	2

@ Constants for local variables
	.equ	LOCAL_VAR_SPACE, 32
	.equ	TIP_CHAR_OFFSET, -8
	.equ	LEFT_SLASH_CHAR_OFFSET, -12
	.equ	RIGHT_SLASH_CHAR_OFFSET, -16
	.equ	START_ITER_OFFSET, -20
	.equ	END_ITER_OFFSET, -24
	.equ	INCR_OFFSET, -28
	.equ	CAP_SIZE_OFFSET, -32
	.equ	I_OFFSET, -36

@ Constants for parameters
	.equ	PARAM_SPACE, 16
	.equ	SIZE_OFFSET, -40
	.equ	FILL_CHAR_OFFSET, -44
	.equ	DIRECTION_OFFSET, -48

@ More constants
	.equ	HALF_DIVISOR, 2		@ Used for dividing variable size in half
	.equ	DOUBLE, 2		@ Used for doubling values
	
	@ Cool S cap directions
	.equ	DIR_UP, 0
	.equ	DIR_DOWN, 1

	@ Cool S whitespace, tip, and border characters
	.equ	SPACE_CHAR, ' '
	.equ	NEWLINE_CHAR, '\n'
	.equ	FORWARD_SLASH_CHAR, '/'
	.equ	BACK_SLASH_CHAR, '\\'
	.equ	CARAT_CHAR, '^'
	.equ	V_CHAR, 'v'


/*
 * Function name: drawCap()
 * Function Prototype: void drawCap( int size, char fillChar, int direction );
 * Description: Draw the cap of Cool S either up or down
 * Parameters: size - width of Cool S
 * 	      fillChar - character to fill Cool S with
 *	      direction - whether cap points up or down
 * Side Effects: prints to stdout
 * Error Conditions: None
 * Return Value: None
 *
 * Registers used:
 *	r0 - size and function arguments and temp storage
 *	r1 - fillChar and function arguments and temp storage
 *	r2 - direction and temp storage
 *	r3 - temp storage
 */
drawCap:
	push	{fp, lr}
	add	fp, sp, FP_OFFSET
	
	@ allocate local var and param space
	sub	sp, sp, LOCAL_VAR_SPACE
	sub	sp, sp, PARAM_SPACE

	@ Store params
	str	r0, [fp, SIZE_OFFSET]
	str	r1, [fp, FILL_CHAR_OFFSET]
	str	r2, [fp, DIRECTION_OFFSET]

	@ Store cap size
	mov	r1, HALF_DIVISOR	
	sdiv	r3, r0, r1
	str	r3, [fp, CAP_SIZE_OFFSET]
	
	@ Top cap or bottom cap
	ldr	r2, [fp, DIRECTION_OFFSET]
	cmp	r2, DIR_UP
	bne	drawBottomCap	
	
	@ tipChar = CARAT_CHAR
	mov	r3, CARAT_CHAR				
	str	r3, [fp, TIP_CHAR_OFFSET]
	
	@ leftSlashChar = FORWARD_SLASH_CHAR
	mov	r3, FORWARD_SLASH_CHAR
	str	r3, [fp, LEFT_SLASH_CHAR_OFFSET]	

	@ rightSlashChar = BACK_SLASH_CHAR
	mov	r3, BACK_SLASH_CHAR
	str	r3, [fp, RIGHT_SLASH_CHAR_OFFSET]	

	@ startIter = 0
	mov	r3, 0
	str	r3, [fp, START_ITER_OFFSET]		

	@ endIter = capSize + 1
	ldr	r3, [fp, CAP_SIZE_OFFSET]
	add	r3, r3, 1
	str	r3, [fp, END_ITER_OFFSET]		

	@ incr = 1
	mov	r3, 1
	str	r3, [fp, INCR_OFFSET]		

	@ Start drawing cap

	@ i = startIter
	ldr	r3, [fp, START_ITER_OFFSET]
	str	r3, [fp, I_OFFSET]			


	@ End while loop if i == endIter
	ldr	r0, [fp, I_OFFSET]
	ldr	r1, [fp, END_ITER_OFFSET]
	cmp	r0, r1
	beq	epilogue

	@ Else enter loop
	b	while_loop


drawBottomCap:
	@ tipChar = V_CHAR
	mov	r3, V_CHAR
	str	r3, [fp, TIP_CHAR_OFFSET]		

	@ leftSlashChar = BACK_SLASH_CHAR
	mov	r3, BACK_SLASH_CHAR
	str	r3, [fp, LEFT_SLASH_CHAR_OFFSET]

	@ rightSlashChar = FORWARD_SLASH_CHAR
	mov	r3, FORWARD_SLASH_CHAR
	str	r3, [fp, RIGHT_SLASH_CHAR_OFFSET]

	@ startIter = capSize
	ldr	r3, [fp, CAP_SIZE_OFFSET]
	str	r3, [fp, START_ITER_OFFSET]

	@ endIter = -1
	mov	r3, -1
	str	r3, [fp, END_ITER_OFFSET]

	@ incr = -1
	mov	r3, -1
	str	r3, [fp, INCR_OFFSET]
 
	
	@ Start drawing cap

	@ i = startIter
	ldr	r3, [fp, START_ITER_OFFSET]
	str	r3, [fp, I_OFFSET]			


	@ End while loop if i == endIter
	ldr	r0, [fp, I_OFFSET]
	ldr	r1, [fp, END_ITER_OFFSET]
	cmp	r0, r1
	beq	epilogue

	@ Else enter loop
	b	while_loop

 @ while loop
while_loop:
	mov	r0, SPACE_CHAR			@ r0 = SPACE_CHAR
	ldr	r1, [fp, CAP_SIZE_OFFSET]	@ r1 = capSize
	ldr	r2, [fp, I_OFFSET]		@ r2 = i
	sub	r1, r1, r2			@ r1 = capSize - i
	bl	outputCharNTimes		@ outputCharNTimes(r0, r1)

	ldr	r2, [fp, I_OFFSET]
	cmp	r2, 0				
	bne	else				@ if i == 0, go to else

@ if loop; draw tip  if it's first/last iteration
if_loop:
	ldr	r0, [fp, TIP_CHAR_OFFSET]
	bl	outputChar			@ outputChar(tipchar)
	b	check_while

@ else; draw cap content
else:
	ldr	r0, [fp, LEFT_SLASH_CHAR_OFFSET]
	bl	outputChar			@ outputChar(leftSlashChar)

	ldr	r0, [fp, FILL_CHAR_OFFSET]	@ r0(arg0) = fillChar
	ldr	r2, [fp, I_OFFSET]		@ r2 = i
	mov	r3, DOUBLE
	mul	r1, r2, r3			@ r1 = i * DOUBLE 
	sub	r1, r1, 1			@ r1(arg1) = r1 - 1
	bl	outputCharNTimes		@ outputCharNTimes(r0, r1)

	ldr	r0, [fp, RIGHT_SLASH_CHAR_OFFSET]
	bl	outputChar			@ outputChar(rightSlashChar)

@ Perform rest of loop and then check while loop condition
check_while:
	mov	r0, SPACE_CHAR			@ r0 = SPACE_CHAR
	ldr	r1, [fp, CAP_SIZE_OFFSET]	@ r1 = capSize
	ldr	r2, [fp, I_OFFSET]		@ r2 = i
	sub	r1, r1, r2			@ r1 = capSize - i
	bl	outputCharNTimes		@ outputCharNTimes(r0, r1)

	mov	r0, NEWLINE_CHAR		@ r0 = NEWLINE_CHAR
	bl	outputChar			@ output(NEWLINE_CHAR)

	ldr	r1, [fp, I_OFFSET]
	ldr	r2, [fp, INCR_OFFSET]
	add	r3, r1, r2			@ i = i + incr
	str	r3, [fp, I_OFFSET]

	ldr 	r2, [fp, END_ITER_OFFSET]
	ldr	r3, [fp, I_OFFSET]
	cmp	r3, r2
	bne	while_loop			@ while(i != endIter)

epilogue:
	sub	sp, fp, FP_OFFSET
	pop	{fp, pc}





