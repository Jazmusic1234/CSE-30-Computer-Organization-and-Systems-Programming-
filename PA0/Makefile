#
# Makefile for CSE 30 -- PA0
# You should not need to change anything in this file.
#

HEADERS		= pa0.h
C_SRCS		= initArray.c pa0.c printInOrder.c printReversed.c
ASM_SRCS	= average3.s

C_OBJS		= $(C_SRCS:.c=.o)
ASM_OBJS	= $(ASM_SRCS:.s=.o)
OBJS		= $(C_OBJS) $(ASM_OBJS)

EXE		= a.out


GCC		= /usr/bin/gcc
ASM		= $(GCC)
RM		= rm

GCC_FLAGS	= -c -g -W -Wall -D__EXTENSIONS__ -std=c99
ASM_FLAGS	= -c -g
LD_FLAGS	= -g -Wall


#
# Standard rules
#

.s.o:
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(ASM_FLAGS) $<
	@echo ""

.c.o:
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Have our project target be named whatever we specify above for EXE.
#

$(EXE):	$(OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(EXE) $(OBJS)
	@echo ""
	@echo "Compilation Successful!"

$(C_OBJS): $(HEADERS)

clean:
	@echo "Cleaning up project directory ..."
	$(RM) -f $(OBJS) $(EXE) core
	@echo ""
	@echo "Clean."

new:
	make clean
	make
