#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "cpu.h"
#include "cartridge.h"
#include "memory.h"
#include "bus.h"

int start_emulator(struct cpu6502 *cpu)
{
    return 0;
}

int main()
{
    
    struct cartridge *cart = cartridge_load_game("games/chip_dale.nes");
    if(NULL==cart)
    {
        fprintf(stderr, "Cannot load ROM file!\n");
        return 1;
    }
    printf("Loaded cartridge %p.\n", cart);

    struct cpu6502 *cpu = cpu_new();
    if(NULL==cpu)
    {
        fprintf(stderr, "Cannot allocate CPU!\n");
        return 1;
    }
    printf("CPU allocated.\n");

    struct nesppu *ppu = ppu_new();
    if(NULL==ppu)
    {
        fprintf(stderr, "Cannot allocate PPU!\n");
        return 1;
    }
    printf("PPU allocated.\n");

    unsigned char *ram = memory_allocate(RAM_SIZE);
    if(NULL==ram)
    {
        fprintf(stderr, "Cannot allocate RAM!\n");
        return 1;
    }
    printf("RAM allocated.\n");

    struct nesbus *bus = bus_new();
    if(NULL==bus)
    {
        fprintf(stderr, "Cannot allocate bus!\n");
        return -1;
    }
    printf("System bus allocated.\n");

    bus->cart = cart;
    bus->ppu = ppu;
    bus->ram = ram;

    cpu->bus = bus;
    start_emulator(cpu);
    return 0;
}
