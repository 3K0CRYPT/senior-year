CC = gcc
LD = $(CC)
SRCFILES = $(wildcard src/*.c)
OBJFILES = $(patsubst src/%.c, bin/%.o, $(SRCFILES))
OBJDEBUG = $(patsubst src/%.c, bin/%.debug.o, $(SRCFILES))
OUTFILE = scheduler
CCFLAGS = -Wall -xc -std=c11
LDFLAGS = 

all: $(OUTFILE)

$(OUTFILE): $(OBJFILES)
	$(LD) $(LDFLAGS) $(OBJFILES) -o $(OUTFILE)

bin/%.o: src/%.c
	$(CC) $(CCFLAGS) -o $@ -c $<

debug: $(OUTFILE).debug
	gdb -tui $(OUTFILE).debug

$(OUTFILE).debug: $(OBJDEBUG)
	$(LD) $(LDFLAGS) $(OBJDEBUG) -o $(OUTFILE).debug

bin/%.debug.o: src/%.c
	$(CC) $(CCFLAGS) -ggdb3 -o $@ -c $<

clean:
	rm -f bin/*.o
	rm -f $(OUTFILE)
	rm -f $(OUTFILE).debug
