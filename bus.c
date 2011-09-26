#include <stdlib.h>
#include <stdio.h>
#include "bus.h"

struct nesbus *bus_new()
{
    return (struct nesbus*)malloc(sizeof(struct nesbus));
}

/* decode memory access */
inline void bus_writeb(struct nesbus *bus, u_int16_t addr, u_int8_t data)
{
    /* 0x0000-0x1FFF -> RAM */
    if(!(addr&0xE000))
    {
        addr &= 0x07FF; /* RAM is 2K */
        bus->ram[addr] = data;
    }
    else if(addr&8000) /*0x8000-0xFFFF -> cartridge */
    {
        cartridge_writeb(bus->cart, addr, data);
    }


}

/*
void bus_writew(struct nesbus *bus, u_int16_t addr, u_int16_t data)
{
}
*/

/* decode memory access */
inline u_int8_t bus_readb(struct nesbus *bus, u_int16_t addr)
{
    /* 0x0000-0x1FFF -> RAM */
    if(!(addr&0xE000))
    {
        addr &= 0x07FF; /* RAM is 2K */
        return bus->ram[addr];
    }
    else if(addr&8000) /*0x8000-0xFFFF -> cartridge */
    {
        return cartridge_readb(bus->cart, addr);
    }

    return 0xFF;
}

/*
u_int16_t bus_readw(struct nesbus *bus, u_int16_t addr)
{
    return 0xFFFF;
}
*/
