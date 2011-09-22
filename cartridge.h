#ifndef _CARTRIDGE_INCLUDED_
#define _CARTRIDGE_INCLUDED_

#include <sys/types.h>

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

#endif /* _CARTRIDGE_INCLUDED_ */
