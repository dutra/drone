CC = avr-gcc
OBJCP = avr-objcopy
LOADER = avrdude

C_DEVICE = atmega32
LO_DEVICE = m32

CINCLUDE = include
SRCDIR = src
OBJDIR = obj

HEADERS = $(wildcard $(CINCLUDE)/*.h)
C_SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJS = $(C_SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.elf)

CFLAGS = -Wall $(DEBUG) -Os -fshort-enums -mmcu=$(C_DEVICE) -I$(CINCLUDE)
OBJCPFLAGS = -j .text -j .data -O ihex
LOFLAGS = -p $(LO_DEVICE) -c usbtiny -e

.PHONY: main send clean

all: main.hex
	@echo "Done!"

send: main.hex
	$(LOADER) $(LOFLAGS) -U flash:w:$<
	@echo "Done sending $(HEX) to $(PORT)"

main.hex: main.elf
	$(OBJCP) $(OBJCPFLAGS) $(OBJDIR)/$< $@
	@echo "Linking complete!"

main.elf: $(C_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(OBJDIR)/$@ $^
	@echo "Compiled "$<" successfully!"

clean:
	rm -rf $(OBJS) main.hex
	@echo "Cleanup complete!"
