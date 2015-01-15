TARGETS=$(CC)-blanusa-noopt $(CC)-blanusa-opt3 $(CC)-blanusa-fastmath

all: $(TARGETS)

COPTS+=-std=c99

$(CC)-blanusa-noopt: blanusa_1.c
	$(CC) $(COPTS) -O0 $^ -lm -o $@

$(CC)-blanusa-opt3: blanusa_1.c
	$(CC) $(COPTS) -O3 $^ -lm -o $@

$(CC)-blanusa-fastmath: blanusa_1.c
	$(CC) $(COPTS) -O3 -ffast-math $^ -lm -o $@

clean:
	rm -f $(TARGETS)
