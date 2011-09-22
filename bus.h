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
    unsigned char*  vram;
};

struct nesbus *bus_new();

#endif /* _BUS_INCLUDED_ */
