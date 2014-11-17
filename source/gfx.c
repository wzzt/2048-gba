/*
 * Basic mode 3 graphics drawing functions
 */

#include "gba.h"
#include "gfx.h"

void draw_bmp(const u16 *bitmap, int x0, int y0)
{
    int w, h, x, y, xmax, ymax, xdiff, ydiff;
    w = bitmap[0];
    h = bitmap[1];
    xmax = x0 + w > SCREEN_WIDTH  ? SCREEN_WIDTH  : x0 + w;
    ymax = y0 + h > SCREEN_HEIGHT ? SCREEN_HEIGHT : y0 + h;
    xdiff = -x0;
    ydiff = -y0 * w;
    if (x0 < 0)
        x0 = 0;
    if (y0 < 0)
        y0 = 0;
    bitmap += 2;
    for (y = y0; y < ymax; ++y)
        for (x = x0; x < xmax; ++x) {
            vid_mem[ y * SCREEN_WIDTH + x ] =
                bitmap[x + xdiff + w * y + ydiff];
        }
}

void fill_screen(COLOR clr)
{
    int i;
    for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
        vid_mem[i] = clr;
}

