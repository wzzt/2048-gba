/*
 * Definitions for mode 3 drawing functions
 */

#ifndef _GFX_H_
#define _GFX_H_

#include "gba.h"

typedef u16 COLOR;

#define CLR_BLACK   0x0000
#define CLR_RED     0x001F
#define CLR_LIME    0x03E0
#define CLR_YELLOW  0x03FF
#define CLR_BLUE    0x7C00
#define CLR_MAG     0x7C1F
#define CLR_CYAN    0x7FE0
#define CLR_WHITE   0x7FFF

void draw_bmp(const u16 *bitmap, int x0, int y0);
void fill_screen(COLOR clr);

#endif

