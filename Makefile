

HEADERS		= pa3.h

ASM_SRCS	= printEnglish.s printIntBinary.s printBase.s printFPBinary.s \
		  checkRange.s strToLong.s

C_SRCS		= main.c processIntToken.c processFPToken.c setFlags.c

OBJS		= main.o printEnglish.o printIntBinary.o printBase.o \
		  printFPBinary.o processIntToken.o processFPToken.o \
		  checkRange.o setFlags.o strToLong.o

EXE		= pa3



GCC		= gcc
ASM		= $(GCC)
LINT		= lint

GCC_FLAGS	= -c -g -Wall -D__EXTENSIONS__ -std=c99
LINT_FLAGS1	= -c -err=warn -m -D__EXTENSIONS__
LINT_FLAGS2	= -u -err=warn -m -x
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
	@echo "Linting each C source file separately ..."
	$(LINT) $(LINT_FLAGS1) $<
	@echo ""
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""



$(EXE):	$(OBJS)
	@echo "2nd phase lint on all C source files ..."
	$(LINT) $(LINT_FLAGS2) *.ln
	@echo ""
	@echo "Linking all object modules ..."
	$(GCC) -O -o $(EXE) $(LD_FLAGS) $(OBJS)
	@echo ""
	@echo "Done."

${C_OBJS}:      ${HEADERS}

clean:
	@echo "Cleaning up project directory ..."
	/usr/bin/rm -f *.o a.out *.ln core $(EXE)
	@echo ""
	@echo "Clean."

new:
	make clean
	make

testprintIntBinary: test.h pa3.h testprintIntBinary.c printIntBinary.s
	@echo "Compiling testprintIntBinary.c"
	gcc -g -o testprintIntBinary testprintIntBinary.c printIntBinary.s
	@echo "Done."

runtestprintIntBinary: testprintIntBinary
	@echo "Running testprintIntBinary"
	@./testprintIntBinary

testprintEnglish: test.h pa3.h testprintEnglish.c printEnglish.s
	@echo "Compiling testprintEnglish.c"
	gcc -g -o testprintEnglish testprintEnglish.c printEnglish.s
	@echo "Done."

testsetFlags: test.h pa3.h checkRange.s strToLong.s testsetFlags.c setFlags.c
	@echo "Compiling testsetFlags.c"
	gcc -g -o testsetFlags testsetFlags.c checkRange.s strToLong.s \
	setFlags.c
	@echo "Done."

testprintBase: test.h pa3.h printBase.s testprintBase.c checkRange.s
	@echo "Compiling testprintBase.c"
	gcc -g -o testprintBase testprintBase.c printBase.s checkRange.s
	@echo "Done."
testprintFPBinary: test.h pa3.h printFPBinary.s testprintFPBinary.c 
	@echo "Compiling testprintFPBinary.c"
	gcc -g -o testprintFPBinary testprintFPBinary.c printFPBinary.s
	@echo "Done."
testprocessIntToken: test.h printBase.s printIntBinary.s strToLong.s \
	setFlags.c pa3.h printEnglish.s processIntToken.c \
	testprocessIntToken.c checkRange.s
	@echo "Compiling testprocesIntToken.c"
	gcc -g -o testprocessIntToken testprocessIntToken.c strToLong.s \
	setFlags.c printBase.s printIntBinary.s printEnglish.s \
	processIntToken.c checkRange.s
	@echo "Done."
testprocessFPToken: test.h strToLong.s printEnglish.s printFPBinary.s \
	strings.h pa3.h testprocessFPToken.c processFPToken.c setFlags.c \
	processIntToken.c checkRange.s printBase.s printIntBinary.s
	@echo "Compiling testprocessFPToken.c"
	gcc -g -o testprocessFPToken testprocessFPToken.c printBase.s \
	printIntBinary.s checkRange.s processIntToken.c pa3.h strToLong.s \
	setFlags.c printFPBinary.s printEnglish.s processFPToken.c
	@echo "Done."
# Add your Unit Tests here.


