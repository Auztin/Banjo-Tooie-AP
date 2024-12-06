N64_INST = mips64/opt/libdragon
CC = $(N64_INST)/bin/mips64-elf-gcc
LD = $(N64_INST)/bin/mips64-elf-ld
ARMIPS = ./armips
ED64ROMCONFIG = libdragon/tools/ed64romconfig

OUTDIR := build
OBJDIR := build/bin
SRCDIR := c
vpath %.c c
vpath %.h c

CFLAGS = -O1 -G0 -fno-reorder-blocks -march=vr4300 -mtune=vr4300 -mno-gpopt -mdivide-breaks -mexplicit-relocs -msoft-float
CFLAGS+= -I include -I $(SRCDIR)
CPPFLAGS = -DF3DEX_GBI_2
LDFLAGS = -L .
LDFLAGS+= -L mips64/opt/libdragon/mips64-elf/lib/soft-float
LDFLAGS+= -L mips64/opt/libdragon/lib/gcc/mips64-elf/14.1.0/soft-float/
LDLIBS = -lc -lgcc

OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(sort $(wildcard $(SRCDIR)/*.c)))

all: clean .WAIT bundle .WAIT asm crc savetype

$(OBJDIR)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS)

$(OBJDIR):
	mkdir -p $@

$(OBJECTS): | $(OBJDIR)

bundle: $(OBJECTS)
	$(CC) -o $(OBJDIR)/boot.o -c $(SRCDIR)/boot/boot.c $(CFLAGS) $(CPPFLAGS)
	$(LD) -T linker_script.ld -o $(OUTDIR)/boot.o -i $(LDFLAGS) $(LDLIBS) -l:$(OBJDIR)/boot.o
	$(LD) -T linker_script.ld -o $(OUTDIR)/bundle.o -i $(patsubst %.o,-l:%.o,$(OBJECTS)) $(LDFLAGS) $(LDLIBS)

asm: $(ARMIPS) build.asm
	$(ARMIPS) -sym2 build/asm_symbols.txt build.asm

crc: asm crc.py ntype.py
	python crc.py

savetype: crc
	$(ED64ROMCONFIG) -w sram256k patched.n64

clean:
	rm -f $(OBJDIR)/*.o
