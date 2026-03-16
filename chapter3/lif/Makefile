CC = gcc
CFLAGS = -O3 -std=gnu11 -Wall
LDLIBS = -lm

TARGETS = lif lif_alt lif_refr syn lif2 network network_delay

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
