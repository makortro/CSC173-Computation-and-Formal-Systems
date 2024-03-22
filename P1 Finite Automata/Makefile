#
# File: Makefile
# Creator: George Ferguson
#
# Sample Makefile distributed with CSC173 Project 1 code bundle
#
# This Makefile builds the test programs for the data structures
# distributed with the bundle, and show how you might use it to
# build YOUR program for the project.
#

PROGRAMS = auto

CFLAGS = -g -std=c99 -Wall -Werror

programs: $(PROGRAMS)

auto: dfa.o nfa.o main.o IntHashSet.o LinkedList.o
	$(CC) -o $@ $^

IntHashSet LinkedList:
	$(CC) -o $@ $(CFLAGS) -DMAIN $@.c

clean:
	-rm $(PROGRAMS) *.o
	-rm -r *.dSYM
