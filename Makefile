CC = avr-gcc
OBJCP = avr-objcopy
LOADER = avrdude

C_DEVICE = atmega644pa
LO_DEVICE = atmega644p

CINCLUDE = include
SRCDIR = src
OBJDIR = obj

HEADERS = $(wildcard $(CINCLUDE)/*.h)
C_SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJS = $(C_SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.elf)

CFLAGS = -Wall -Os -fshort-enums -std=gnu11 -mmcu=$(C_DEVICE) -I$(CINCLUDE) -I.
OBJCPFLAGS = -j .text -j .data -O ihex
LOFLAGS = -p $(LO_DEVICE) -c usbtiny -e
LDFLAGS = -Wl,-Map=$(OBJDIR)/drone.map -lm

.PHONY: main send size clean

all: main.hex
	@echo "Done!"

send: main.hex
	$(LOADER) $(LOFLAGS) -U flash:w:$<
	@echo "Done sending $(HEX) to $(PORT)"

main.hex: main.elf
	$(OBJCP) $(OBJCPFLAGS) $(OBJDIR)/$< $@
	@echo "Linking complete!"

main.elf: $(C_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(OBJDIR)/$@ $^
	@echo "Compiled "$<" successfully!"

size: SIZE = `cat main.hex | tail -2 | head -1 -c 3 | tail -c 2`
size: ADDRESS = `cat main.hex | tail -2 | head -1 -c 7 | tail -c 4`
size: main.hex
	@echo -n "Size is "
	@echo "ibase=16; $(SIZE) + $(ADDRESS)" | bc | xargs echo -n
	@echo " bytes"

clean:
	rm -rf $(OBJS) main.hex
	@echo "Cleanup complete!"
