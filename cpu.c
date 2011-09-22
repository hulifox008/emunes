#include <stdlib.h>
#include "common.h"
#include "cpu.h"

struct cpu6502 *cpu_new()
{   
    return (struct cpu6502 *)malloc(sizeof(struct cpu6502));
}

void cpu_reset(struct cpu6502 *cpu)
{
    
}
