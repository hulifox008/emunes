#include <stdlib.h>
#include "ppu.h"

struct nesppu *ppu_new()
{
    return (struct nesppu*)malloc(sizeof(struct nesppu));
}
