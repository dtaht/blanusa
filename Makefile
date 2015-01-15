TARGETS=$(CC)-blanusa-noopt.test $(CC)-blanusa-opt3.test $(CC)-blanusa-fastmath.test
ASM= $(patsubst %.test,%.s,$(TARGETS))

all: $(TARGETS)

asm: $(ASM)

test: $(TARGETS)
	@echo $(foreach t,$(TARGETS),$(shell ./$(t) | head -1))
	@echo $(foreach t,$(TARGETS),$(shell ./$(t) | head -1))
	@echo $(foreach t,$(TARGETS),$(shell ./$(t) | head -1))
	@echo $(foreach t,$(TARGETS),$(shell ./$(t) | head -1))
	@echo $(foreach t,$(TARGETS),$(shell ./$(t) | head -1))
	@echo $(foreach t,$(TARGETS),$(shell ./$(t) | head -1))
	@echo $(foreach t,$(TARGETS),$(shell ./$(t) | head -1))
	@echo $(foreach t,$(TARGETS),$(shell ./$(t) | head -1))
	@echo $(foreach t,$(TARGETS),$(shell ./$(t) | head -1))
	@echo $(foreach t,$(TARGETS),$(shell ./$(t) | head -1))

COPTS+=-std=gnu99 -lrt
ifdef DEBUG
COPTS+=-g
endif

$(CC)-blanusa-noopt.test: blanusa_1.c
	$(CC) $(COPTS) -O0 $^ -lm -o $@

$(CC)-blanusa-opt3.test: blanusa_1.c
	$(CC) $(COPTS) -O3 $^ -lm -o $@

$(CC)-blanusa-fastmath.test: blanusa_1.c
	$(CC) $(COPTS) -O3 -ffast-math $^ -lm -o $@

$(CC)-blanusa-noopt.s: blanusa_1.c
	$(CC) $(COPTS) -O0 $^ -lm -S -o $@

$(CC)-blanusa-opt3.s: blanusa_1.c
	$(CC) $(COPTS) -O3 $^ -lm -S -o $@

$(CC)-blanusa-fastmath.s: blanusa_1.c
	$(CC) $(COPTS) -O3 -ffast-math $^ -S -lm -o $@

clean:
	rm -f $(TARGETS) $(ASM)
	
