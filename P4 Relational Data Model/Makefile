CC = gcc

CFLAGS = -g -std=c99 -Wall -Werror

PROGRAMS = auto

programs: $(PROGRAMS)

auto: main.o CDH.o CP.o CR.o CSG.o Database.o SNAP.o
	$(CC) -o $@ $(CFLAGS) $^

clean:
	-rm $(PROGRAMS) *.o