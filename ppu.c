#include <stdlib.h>
#include <assert.h>
#include "ppu.h"
#include "common.h"

struct nesppu *ppu_new()
{
    struct nesppu *ppu = (struct nesppu*)malloc(sizeof(struct nesppu));
    ppu->vram = malloc(VRAM_SIZE);
    return ppu;
}

void ppu_set_nmi_porc(struct nesppu *ppu, void (*nmi_proc)(void *data))
{
    assert(NULL!=ppu);
    ppu->nmi_proc = nmi_proc;
}
