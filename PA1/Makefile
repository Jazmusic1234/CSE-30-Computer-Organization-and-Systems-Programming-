#
# Makefile for CSE 30 -- PA1
# You should not need to change anything in this file.
#
# XXX DO NOT EDIT
#

HEADERS		= pa1.h pa1Strings.h
TEST_HEADERS	= $(HEADERS) test.h
C_SRCS		= pa1.c drawCrissCross.c outputCharNTimes.c
ASM_SRCS	= isDividable.s myRem.s outputChar.s intervalContains.s \
		  drawCap.s

# REG = only used in regular program; EC = only used in EC program.
REG_C_SRCS	= drawCoolS.c
EC_C_SRCS	= drawCoolSEC.c
REG_ASM_SRCS	= # N/A
EC_ASM_SRCS	= sumOfDigitsEC.s

C_OBJS		= $(C_SRCS:.c=.o)
ASM_OBJS	= $(ASM_SRCS:.s=.o)
REG_C_OBJS	= $(REG_C_SRCS:.c=.o)
EC_C_OBJS	= $(EC_C_SRCS:.c=.o)
REG_ASM_OBJS	= $(REG_ASM_SRCS:.s=.o)
EC_ASM_OBJS	= $(EC_ASM_SRCS:.s=.o)
OBJS		= $(C_OBJS) $(ASM_OBJS) $(REG_C_OBJS) $(REG_ASM_OBJS)
EC_OBJS		= $(C_OBJS) $(ASM_OBJS) $(EC_C_OBJS) $(EC_ASM_OBJS)

EXE		= pa1
EC_EXE		= pa1EC
TEST_EXES	= testisDividable testmyRem testoutputChar \
		  testoutputCharNTimes testintervalContains testsumOfDigitsEC

GCC		= gcc
ASM		= $(GCC)
RM		= rm

DEBUG_FLAGS	= -g
GCC_FLAGS	= -c $(DEBUG_FLAGS) -std=c99 -pedantic -Wall -D__EXTENSIONS__
ASM_FLAGS	= -c $(DEBUG_FLAGS)
LD_FLAGS	= $(DEBUG_FLAGS) -Wall

OPT_FLAGS	= -O3 -fstack-protector-all
OPT_GCC_FLAGS	= $(subst $(DEBUG_FLAGS),$(OPT_FLAGS),$(GCC_FLAGS))
OPT_ASM_FLAGS	= $(subst $(DEBUG_FLAGS),$(OPT_FLAGS),$(ASM_FLAGS))
OPT_LD_FLAGS	= $(subst $(DEBUG_FLAGS),$(OPT_FLAGS),$(LD_FLAGS))


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
# Simply have our project target be a single default $(EXE) executable.
#

$(EXE):	$(OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(EXE) $(OBJS)
	@echo ""
	@echo "Compilation Successful!"

$(EC_EXE): $(EC_OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(EC_EXE) $(EC_OBJS)
	@echo ""
	@echo "Compilation Successful!"

$(C_OBJS): $(HEADERS)


clean:
	@echo "Cleaning up project directory ..."
	$(RM) -f *.o $(EXE) $(EC_EXE) core a.out $(TEST_EXES) *$(OPT_EXT)
	@echo ""
	@echo "Clean."

#
# Unit test targets
#

# List dependencies for tester executable in variable suffixed with "Deps"
testisDividableDeps = testisDividable.o isDividable.o myRem.o
testmyRemDeps = testmyRem.o myRem.o
testoutputCharDeps = testoutputChar.o outputChar.o
testoutputCharNTimesDeps = testoutputCharNTimes.o outputCharNTimes.o \
			   outputChar.o
testintervalContainsDeps = testintervalContains.o intervalContains.o
testsumOfDigitsECDeps = testsumOfDigitsEC.o sumOfDigitsEC.o myRem.o

OPT_EXT = -opt

# Optimized object file rules.
%$(OPT_EXT).o: %.s
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(OPT_ASM_FLAGS) -o $(<:.s=$(OPT_EXT).o) $<
	@echo ""

%$(OPT_EXT).o: %.c
	@echo "Compiling each C source file separately ..."
	$(GCC) $(OPT_GCC_FLAGS) -o $(<:.c=$(OPT_EXT).o) $<
	@echo ""

# Rules for compiling tester toplevels.
$(TEST_EXES): $(TEST_HEADERS)
	@echo "Compiling $@ ..."
	$(GCC) $(LD_FLAGS) -o $@ $(filter %.o, $^)
	@echo "Compilation Successful!"

TEST_OPT_EXES = $(TEST_EXES:=$(OPT_EXT))
$(TEST_OPT_EXES): $(TEST_HEADERS)
	@echo "Compiling $@ ..."
	$(GCC) $(OPT_LD_FLAGS) -o $@ $(filter %.o, $^)
	@echo "Compilation Successful!"

# Lay out dependencies for each test file (regular and optimized).
define testRule
$(1): $$($(1)Deps)				# Regular dependencies.
$(1)$$(OPT_EXT): $$($(1)Deps:.o=$$(OPT_EXT).o)	# Optimized .o dependencies.
endef

# This calls the above function on each test file target, generating rules
# for each tester file's regular and optimized executables.
$(foreach test,$(TEST_EXES),$(eval $(call testRule,$(test))))

new:
	make clean
	make
