CC = sdcc
AR = sdar

SOURCES = $(wildcard *.c)
OBJS = $(patsubst %.c, %.rel, $(SOURCES))

all: mnome.ihx

include $(patsubst %.c, .%.d, $(SOURCES))

.%.d: %.c
	$(CC) -MM $< > $@

%.rel:
	$(CC) -c $< -o $@

mnome.ihx: $(OBJS)
	$(CC) $^ -o $@
	packihx mnome.ihx > mnome.hex

clean:
	rm -f *.asm *.lst *.rel *.rst *.sym *.mem *.map *.lk *.ihx *.hex

install:
	stcgal -P stc89 -p /dev/tty.SLAB_USBtoUART -b9600 mnome.hex
