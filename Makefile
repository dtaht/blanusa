TARGETS=$(CC)-blanusa-noopt $(CC)-blanusa-opt3 $(CC)-blanusa-fastmath

all: $(TARGETS)
#asm: $(patsubst ,.asm,$TARGETS)

COPTS+=-std=gnu99 -lrt

$(CC)-blanusa-noopt: blanusa_1.c
	$(CC) $(COPTS) -O0 $^ -lm -o $@

$(CC)-blanusa-opt3: blanusa_1.c
	$(CC) $(COPTS) -O3 $^ -lm -o $@

$(CC)-blanusa-fastmath: blanusa_1.c
	$(CC) $(COPTS) -O3 -ffast-math $^ -lm -o $@

$(CC)-blanusa-noopt.s: blanusa_1.c
	$(CC) $(COPTS) -O0 $^ -lm -S -o $@

$(CC)-blanusa-opt3.s: blanusa_1.c
	$(CC) $(COPTS) -O3 $^ -lm -S -o $@

$(CC)-blanusa-fastmath.s: blanusa_1.c
	$(CC) $(COPTS) -O3 -ffast-math $^ -S -lm -o $@

clean:
	rm -f $(TARGETS)
