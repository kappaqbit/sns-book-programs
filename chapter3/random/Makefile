CC = gcc
CFLAGS = -O3 -std=gnu11 -Wall
LDLIBS = -lm

SFMTDIR = ../misc/SFMT-src-1.5.1
SFMTFLAGS = -I$(SFMTDIR) -DSFMT_MEXP=19937

TARGETS = random
MISC_OBJS = SFMT.o timer.o

.PHONY: all run clean distclean

all: run

$(TARGETS): %: %.o $(MISC_OBJS)
	$(CC) $(CFLAGS) $(SFMTFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(SFMTFLAGS) -c $<

SFMT.o: $(SFMTDIR)/SFMT.c $(SFMTDIR)/SFMT.h
	$(CC) $(CFLAGS) $(SFMTFLAGS) -c $<

timer.o: ../misc/timer.c
	$(CC) $(CFLAGS) -c $<

run: $(TARGETS)
	for t in $(TARGETS); do ./$$t > $$t.dat; done

clean:
	rm -f $(TARGETS) *.o

distclean: clean
	rm -f *.dat
