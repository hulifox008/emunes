#ifndef _CARTRIDGE_INCLUDED_
#define _CARTRIDGE_INCLUDED_

#include <sys/types.h>

#define     MIRRORING_MASK  1
#define     SRAM_ENABLED    (1<<1)
#define     TRAINER_ENABLED (1<<2)
#define     FOUR_SCREEN     (1<<3)

struct ines_header
{
    char        magic[4]; /* "NES\x1a" */    
    u_int8_t    prg_rom_size; 
    u_int8_t    chr_rom_size;
    u_int8_t    mapper1;
    u_int8_t    mapper2;
    u_int8_t    unused[8];
}__attribute__((packed));

struct cartridge
{
    struct ines_header header;
    unsigned char *prg_rom;
    unsigned char *chr_rom;
};

struct cartridge * cartridge_load_game(const char *filename);

void cartridge_free(struct cartridge *cart);

u_int8_t cartridge_readb(struct cartridge *cart, u_int16_t addr);

void cartridge_writeb(struct cartridge *cart, u_int16_t addr, u_int8_t data);

#endif /* _CARTRIDGE_INCLUDED_ */
