N64_INST = mips64/opt/libdragon
CC = $(N64_INST)/bin/mips64-elf-gcc
LD = $(N64_INST)/bin/mips64-elf-ld
ARMIPS = ./armips
ED64ROMCONFIG = libdragon/tools/ed64romconfig

CFLAGS = -O1 -G0 -fno-reorder-blocks -march=vr4300 -mtune=vr4300 -mno-gpopt -mdivide-breaks -mexplicit-relocs -I include
CPPFLAGS = -DF3DEX_GBI_2

OUTDIR := build
OBJDIR := build/bin
SRCDIR := c
vpath %.c c
vpath %.h c

OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(sort $(wildcard $(SRCDIR)/*.c)))

.PHONY: all clean bundle asm crc savetype

all: clean bundle asm crc savetype

$(OBJDIR)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS)

$(OBJDIR):
	mkdir -p $@

$(OBJECTS): | $(OBJDIR)

bundle: $(OBJECTS)
	$(CC) -o $(OBJDIR)/boot.o -c $(SRCDIR)/boot/boot.c $(CFLAGS) $(CPPFLAGS)
	$(LD) -T linker_script.ld -o $(OUTDIR)/boot.o -i -L. -l:$(OBJDIR)/boot.o
	$(LD) -T linker_script.ld -o $(OUTDIR)/bundle.o -i -L. $(patsubst %.o,-l:%.o,$(OBJECTS)) -L mips64/opt/libdragon/mips64-elf/lib -l c

asm: $(ARMIPS) build.asm
	$(ARMIPS) -sym2 build/asm_symbols.txt build.asm

crc: crc.py ntype.py
	python crc.py

savetype:
	$(ED64ROMCONFIG) -w sram256k patched.n64

clean:
	rm -f $(OBJDIR)/*.o
