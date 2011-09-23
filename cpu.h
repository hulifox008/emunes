#ifndef _CPU_INCLUDED_
#define _CPU_INCLUDED_

#include "bus.h"

struct cpu6502
{
    /* Registers */
    u_int16_t   pc;
    u_int8_t    sp;
    u_int8_t    a;
    u_int8_t    x;
    u_int8_t    y;
    u_int8_t    p;  /* Processor Status */

    int     cycles; /* CPU cycles in current video frame */

    struct nesbus *bus; /* System bus the CPU is connected to. */
};

struct cpu6502 *cpu_new();

void cpu_reset(struct cpu6502 *cpu);

/* Execute one instruction */
void cpu_step(struct cpu6502 *cpu);

void cpu_nmi(struct cpu6502 *cpu);

#endif /* _CPU_INCLUDED_ */
