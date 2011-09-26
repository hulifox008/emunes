#ifndef _CPU_INCLUDED_
#define _CPU_INCLUDED_

#include "bus.h"

#define	PF_CARRY	0x01
#define PF_ZERO		0x02
#define PF_INT      0x04
#define PF_DEC		0x08
#define PF_BRK		0x01
#define PF_OVERFLOW	0x04
#define PF_SIGN		0x08

struct cpu6502
{
    /* Registers */
    u_int16_t   pc;
    u_int8_t    sp;
    u_int8_t    a;
    u_int8_t    x;
    u_int8_t    y;
    u_int8_t    p;  /* Processor Status */

    unsigned int    cycles; /* CPU cycles in current video frame */

    struct nesbus   *bus; /* System bus the CPU is connected to. */
    int     disasm; /* whether to print disassembled code */
};

struct cpu6502 *cpu_new();

void cpu_reset(struct cpu6502 *cpu);

/* Execute one instruction */
void cpu_step(struct cpu6502 *cpu);

void cpu_nmi(struct cpu6502 *cpu);

#endif /* _CPU_INCLUDED_ */
