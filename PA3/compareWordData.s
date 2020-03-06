/*
 * Filename: compareWordData.s
 * Author: Jasmine Chen
 * UserId: cs30xax
 * Date: 5/11/2019
 * Sources of Help: write up, Week 6 Discussion Worksheet, piazza
 */

 	.cpu	cortex-a53	@ Our Raspberry Pi
	.syntax	unified		@ Modern syntax

	.equ	FP_OFFSET, 4

	// Local variables
	.equ	LOCAL_SPACE, 16
	.equ	WORD1_OFFSET, -8
	.equ	WORD2_OFFSET, -12
	.equ	HASH1_OFFSET, -16
	.equ	HASH2_OFFSET, -20

	// Formal parameters
	.equ	PARAM_SPACE, 8
	.equ	W1_OFFSET, -24
	.equ	W2_OFFSET, -28

	.equ	MAX_WORD_SIZE, 48

	.section	.rodata	@ Need .section asm directive for .rodata

	.global	compareWordData
	.text
	.align	2

/*
 * Function Name: compareWordData()
 * Function Prototype: int compareWordData( const char * w1, 
 *	const char * w2 );
 * Description: Compare hash values 2 void pointers and then compare words
 * Parameters: w1 - first word to be compared
 *	       w2 - second word to be compared
 * Side Effects: None
 * Error Conditions: None
 * Return Value: if w1 has smaller hashValue than w2 or hashValues are same but
 *			strncmp returns value < 0, return -1
 *		 if w1 has larger hashValue than w2 or hashValues are same but
 *			strncmp returns value > 0, return 1
 *		 if hashValues are same and strncmp returns 0, return 0
 *
 * Registers used:
 *	r0 - w1
 *	r1 - w2 and temporarily store variables for calculations
 *	r2 - temporarily store variables for calculations
 *
 * Stack variables:
 *	word1 - [fp - 8] - holds w1->word
 *	word2 - [fp - 12] - holds w2->word
 *	hash1 - [fp - 16] - holds w1->hashValue
 *	hash2 - [fp - 20] - holds w2->hashValue
 *	w1 - [fp - 24] - pointer to w1
 *	w2 - [fp - 28] - pointer to w2
 */
compareWordData:

	@ Prologue
	push	{fp, lr}			@ save caller's frame pointer

	add	fp, sp, FP_OFFSET		@ set fp to base of saved regs

	sub	sp, sp, LOCAL_SPACE		@ Allocate loval space

	// Store params
	sub 	sp, sp, PARAM_SPACE		@ Allocate param space
	str	r0, [fp, W1_OFFSET]		@ Store w1
	str	r1, [fp, W2_OFFSET]		@ Store w2

	// Get hash1 and hash2
	ldr	r2, =G_HASHVALUE_OFFSET		@ Load address of hashOffset
	ldr	r2, [r2]			@ Load hashOffset
	ldr	r0, [fp, W1_OFFSET]		@ Load w1
	ldr	r3, [r0, r2]			@ Load w1->hashValue
	str	r3, [fp, HASH1_OFFSET]		@ Store w1->hashValue

	ldr	r2, =G_HASHVALUE_OFFSET		@ Load address of hashOffset
	ldr	r2, [r2]			@ Load hashOffset
	ldr	r1, [fp, W2_OFFSET]		@ Load w2
	ldr	r3, [r1, r2]			@ Load w2->hashValue
	str	r3, [fp, HASH2_OFFSET]		@ Store w2->hashValue

	// If w1 has smaller hashValue than w2, branch less
	ldr	r0, [fp, HASH1_OFFSET]		@ Load hash1
	ldr	r1, [fp, HASH2_OFFSET]		@ Load hash2
	cmp	r0, r1
	blo	less				@ if hash1<hash2, branch less

	// If w1 has larger hashValue than w2, branch more
	ldr	r0, [fp, HASH1_OFFSET]		@ Load hash1
	ldr	r1, [fp, HASH2_OFFSET]		@ Load hash2
	cmp	r0, r1
	bhi	more				@ if hash1>hash2, branch more

	// Else(same hashvalue)
	// If strncmp < 0, branch less
	//ldr	r2, =G_WORD_OFFSET		@ Load address of wordOffset
	//ldr	r2, [r2]			@ Load wordOffset
	ldr	r0, [fp, W1_OFFSET]		@ Load w1
	//add	r0, r1, r2			@ Get address of w1->word

	//ldr	r2, =G_WORD_OFFSET		@ Load address of wordOffset
	//ldr	r2, [r2]			@ Load wordOffset
	ldr	r1, [fp, W2_OFFSET]		@ Load w2
	//add	r1, r3, r2			@ Get address of w2->word
	
	mov	r2, MAX_WORD_SIZE		@ arg3 is MAX_WORD_SIZE	
	bl	strncmp				@ strncmp(w1->word, w2->word)
	cmp	r0, 0
	blt	less				@ if strncmp < 0, branch less

	// If strncmp > 0, branch more
	ldr	r2, =G_WORD_OFFSET		@ Load address of wordOffet
	ldr	r2, [r2]			@ Load wordOffset
	ldr	r1, [fp, W1_OFFSET]		@ Load w1
	add	r0, r1, r2			@ Get address of w1->word
	
	ldr	r2, =G_WORD_OFFSET		@ Load address of wordOffset
	ldr	r2, [r2]			@ Load wordOffset
	ldr	r3, [fp, W2_OFFSET]		@ Load w2
	add	r1, r3, r2			@ Get address of w2->word
	
	mov	r2, MAX_WORD_SIZE		@ arg3 is MAX_WORD_SIZE	
	bl	strncmp				@ strncmp(w1->word, w2->word)
	cmp	r0, 0
	bgt	more				@ if strncmp > 0, branch more

	// Else(same hashValue and strncmp returns 0)
	mov	r0, 0
	b	epilogue

less:
	mov	r0, -1
	b	epilogue			@ return -1

more:
	mov	r0, 1
	b	epilogue			@ return 1

epilogue:
	sub	sp, fp, FP_OFFSET
	
	pop	{fp, pc}
