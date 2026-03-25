CC = gcc
CFLAGS = -O3 -std=gnu11 -Wall
LDLIBS = -lm

SFMTDIR = ./misc/SFMT-src-1.5.1
SFMTFLAGS = -I$(SFMTDIR) -DSFMT_MEXP=19937

TARGETS = ocular_dominance
MISC_OBJS = SFMT.o

.PHONY: all run clean distclean

all: run

$(TARGETS): %: %.o $(MISC_OBJS)
	$(CC) $(CFLAGS) $(SFMTFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(SFMTFLAGS) -c $<

SFMT.o: $(SFMTDIR)/SFMT.c $(SFMTDIR)/SFMT.h
	$(CC) $(CFLAGS) $(SFMTFLAGS) -c $<

run: $(TARGETS)
	./ocular_dominance

clean:
	rm -f $(TARGETS) *.o

distclean: clean
	rm -f *.dat
