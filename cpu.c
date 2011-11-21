#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "cpu.h"
#include "bus.h"

#define instruction_impl(code, name) \
void name(struct cpu6502 *cpu, u_int8_t instruction)

typedef void (*INSTRUCTION)(struct cpu6502 *cpu, u_int8_t instruction);

/* 6502 instructions 
 * each instructiio has the function prototype: void (*INSTRUCTION)(struct cpu6502 *cpu, u_int8_t instruction) */
void unimp(struct cpu6502 *cpu, u_int8_t instruction)
{
    fprintf(stderr, "[ERROR] Unimplemented instruction - 0x%04X:0x%02X\n", cpu->pc, instruction);
    exit(1);
}

instruction_impl(0x78, SEI)
{
    if(cpu->disasm)
        printf("%04X: %02X              SEI\n", cpu->pc, instruction);
    cpu->p |= PF_INT;
    cpu->pc++;
    cpu->cycles += 2;
}

instruction_impl(0x4c, JMP_abs)
{
    u_int8_t l = bus_readb(cpu->bus, cpu->pc+1);
    u_int8_t h = bus_readb(cpu->bus, cpu->pc+2);
    if(cpu->disasm)
        printf("%04X: %02X %02X %02X   JMP $%02X%02X\n", cpu->pc, instruction, l, h, h, l);
    cpu->pc = (h<<8)+l;
    cpu->cycles += 3;
}

instruction_impl(0xd8, CLV)
{
    if(cpu->disasm)
        printf("%04X: %02X              CLV\n", cpu->pc, instruction);
    cpu->p &= PF_OVERFLOW;
    cpu->pc++;
    cpu->cycles += 2;
}

instruction_impl(0xee, INC_abs)
{
    u_int8_t l = bus_readb(cpu->bus, cpu->pc+1);
    u_int8_t h = bus_readb(cpu->bus, cpu->pc+2);
    u_int8_t v;
    if(cpu->disasm)
        printf("%04X: %02X %02X %02X    INC $%02X%02X\n", cpu->pc, instruction, l, h, h, l);

    v = bus_readb(cpu->bus, l|h<<8)+1;
    bus_writeb(cpu->bus, l|h<<8, v);
    
    cpu->p = v? (cpu->p & ~PF_ZERO) : (cpu->p | PF_ZERO);
    cpu->pc+=3;
    cpu->cycles += 6;
}

INSTRUCTION instruction_table[256] = {
/*0x00 - 0x0F*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
/*0x10 - 0x1F*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
/*0x20 - 0x2F*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
/*0x30 - 0x3F*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
/*0x40 - 0x4F*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, JMP_abs, unimp, unimp, unimp, 
/*0x50 - 0x5F*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
/*0x60 - 0x6F*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
/*0x70 - 0x7F*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
SEI,   unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
/*0x80 - 0x8F*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
/*0x90 - 0x9F*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
/*0xa0 - 0xaF*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
/*0xb0 - 0xbF*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
/*0xc0 - 0xcF*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
/*0xd0 - 0xdF*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
CLV,   unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
/*0xe0 - 0xeF*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, unimp, unimp, INC_abs, unimp, 
/*0xf0 - 0xfF*/
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
unimp, unimp, unimp, unimp, unimp, unimp, unimp, unimp, 
};

struct cpu6502 *cpu_new()
{   
    struct cpu6502 *cpu = (struct cpu6502 *)malloc(sizeof(struct cpu6502));
    cpu->disasm = 1;
    return cpu;
}

void cpu_reset(struct cpu6502 *cpu)
{    
    cpu->pc = bus_readb(cpu->bus, 0xFFFC) | bus_readb(cpu->bus, 0xFFFD)<<8;
}

void cpu_step(struct cpu6502 *cpu)
{
    u_int8_t instruction = bus_readb(cpu->bus, cpu->pc);
    instruction_table[instruction](cpu, instruction);
}
