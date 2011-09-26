#ifndef _BUS_INCLUDED_
#define _BUS_INCLUDED_

/* This is the NES bus. It decodes memory access to different devices. */

#include "cartridge.h"
#include "ppu.h"
#include "memory.h"

struct nesbus
{
    struct cartridge *cart;
    struct nesppu   *ppu;
    unsigned char*  ram;
};

struct nesbus *bus_new();

void bus_writeb(struct nesbus *bus, u_int16_t addr, u_int8_t data);
void bus_writew(struct nesbus *bus, u_int16_t addr, u_int16_t data);

u_int8_t bus_readb(struct nesbus *bus, u_int16_t addr);
u_int16_t bus_readw(struct nesbus *bus, u_int16_t addr);

#endif /* _BUS_INCLUDED_ */
