CC = gcc
CFLAGS = -O3 -std=gnu11 -Wall
LDLIBS = -lm

TARGETS = hh hh_1_spike fr sfa ia ia_fr

.PHONY: all run clean distclean

all: run

$(TARGETS): %: %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

run: $(TARGETS)
	for t in $(TARGETS); do ./$$t > $$t.dat; done

clean:
	rm -f $(TARGETS) *.o

distclean: clean
	rm -f *.dat
