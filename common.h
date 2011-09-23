#ifndef _COMMON_INCLUDED_
#define _COMMON_INCLUDED_

#include <sys/types.h>

#define	RAM_SIZE	0x800
#define VRAM_SIZE   0x4000

#define PIXEL_PER_SCANLINE  341
#define SCANLINES_PER_FRAME 262

#define PPUCYCLES_PER_FRAME (PIXEL_PER_SCANLINE * SCANLINES_PER_FRAME)

#define PPU_CPU_RATIO       3 /* 1 CPU cycle = 3 PPU cycles */

#endif /* _COMMON_INCLUDED_ */                      

