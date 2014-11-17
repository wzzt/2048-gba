/*
 * Non-inline functions and global variables for GBA functionality
 */

#include "gba.h"

/* Store ~REG_KEYINPUT when key_poll() is called */
u16 __key_curr = 0;
u16 __key_prev = 0;

s32 __randn = 0;

void key_poll()
{
        __key_prev = __key_curr;
        __key_curr = ~REG_KEYINPUT & KEY_MASK;
}

s32 srandf(s32 seed)
{
        s32 old = __randn;
        __randn = seed;
        return old;
}

