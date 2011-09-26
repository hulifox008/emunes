CFLAGS += -Werror -Wall

OBJS = cpu.o ppu.o cartridge.o emunes.o bus.o memory.o

emunes: ${OBJS}
	${CC} -o $@ $^ ${CFLAGS}

%.o: %.c
	${CC} -c -o $@ $< ${CFLAGS}

.PHONY: clean
clean:
	rm -f *.o
	rm -f emunes 

