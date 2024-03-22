#
# File: Makefile
# Creator: George Ferguson
# Created: Mon Nov 28 13:52:02 2016
# Time-stamp: <Wed Apr  6 11:18:57 EDT 2022 ferguson>
#

SRCS = Boolean.c Gates.c Circuit.c main.c
HDRS = Boolean.h Gates.h Circuit.h
OBJS = $(SRCS:.c=.o)
EXE = boosim
ZIPDIR = CSC173 Project 5 Boolean Circuit Simulator

CFLAGS = -std=c99 -Wall -Werror -g

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS)

valgrind:
	valgrind ./$(EXE)

clean:
	-rm $(OBJS) $(EXE)