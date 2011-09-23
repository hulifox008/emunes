#ifndef _PPU_INCLUDED_
#define _PPU_INCLUDED_

struct nesppu
{
    unsigned char *vram;
    void (*nmi_proc)(void *data);
};

struct nesppu * ppu_new();

void ppu_set_nmi_porc(struct nesppu *ppu, void (*nmi_proc)(void *data));

/* run ppu for specified cycles */
void ppu_run(struct nesppu *ppu, int cycles);

void ppu_writeb(struct nesppu *ppu, u_int8_t addr, u_int8_t data);

u_int8_t ppu_readb(struct nesppu *ppu, u_int8_t addr);

#endif /* _PPU_INCLUDED_ */
