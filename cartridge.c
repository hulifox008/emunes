#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "cartridge.h"


struct cartridge *cartridge_load_game(const char *filename)
{
    assert(NULL!=filename);
    struct cartridge * cart = NULL;
    off_t size;
    
    cart = (struct cartridge*)malloc(sizeof(struct cartridge));
    if(NULL==cart)
    {
        goto out;
    }
    memset(cart, 0, sizeof(struct cartridge));

    int fd = open(filename, O_RDONLY);
    if(-1==fd)
    {
        goto out;
    }

    struct stat st = {0};
    fstat(fd, &st);
    size = st.st_size;

    printf("ROM file size: %ld bytes\n", size);
    if(size<sizeof(struct ines_header))
    {
        goto out;
    }

    read(fd, &cart->header, sizeof(cart->header));

    if(strncmp(cart->header.magic, "NES\x1a", 4)!=0)
    {
        fprintf(stderr, "File magic doesn't match!\n");
        goto out;
    }

    printf("PRG ROM: %dK\n", cart->header.prg_rom_size*16); 
    printf("CHR ROM: %dK\n", cart->header.chr_rom_size*8); 

    int prg_size = cart->header.prg_rom_size*16*1024;
    int chr_size = cart->header.chr_rom_size*8*1024;
    if(size < (prg_size + chr_size + sizeof(cart->header)))
    {
        fprintf(stderr, "Invalid ROM File!\n");
        goto out;
    }

    cart->prg_rom = malloc(prg_size);
    cart->chr_rom = malloc(chr_size);
    if(NULL==cart->prg_rom || NULL==cart->chr_rom)
    {
        goto out;
    }

    if(prg_size != read(fd, cart->prg_rom, prg_size))
    {
        goto out;
    }

    if(chr_size != read(fd, cart->chr_rom, chr_size))
    {
        goto out;
    }

    close(fd);
    return cart;

out:
    if(fd!=-1)
        close(fd);
    cartridge_free(cart);   
    return NULL;
}

void cartridge_free(struct cartridge *cart)
{
    if(NULL!=cart)
    {
        if(NULL!=cart->prg_rom)
            free(cart->prg_rom);
        if(NULL!=cart->chr_rom)
            free(cart->chr_rom);

       free(cart);
    }
}

/* addr is in 0x8000 - 0xFFFF */
inline u_int8_t cartridge_readb(struct cartridge *cart, u_int16_t addr)
{
    /* TODO: Implement mapper ... */
    return cart->prg_rom[addr&0x7FFF];
}

/* addr is in 0x8000 - 0xFFFF */
inline void cartridge_writeb(struct cartridge *cart, u_int16_t addr, u_int8_t data)
{
    /* TODO: Implement mapper ... */
        
}
