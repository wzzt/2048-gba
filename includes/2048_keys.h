/*
 * Definitions and inline functions for detecting key-press combinations
 */

#ifndef _2048_KEYS_H_
#define _2048_KEYS_H_

#include "gba.h"

/* Key combination definitions */
#define KEY_ARROWS (KEY_UP | KEY_RIGHT | KEY_LEFT | KEY_DOWN)
#define KEY_UR (KEY_UP | KEY_RIGHT)
#define KEY_UL (KEY_UP | KEY_LEFT)
#define KEY_DL (KEY_DOWN | KEY_LEFT)
#define KEY_DR (KEY_DOWN | KEY_RIGHT)
#define KEY_RL (KEY_RIGHT | KEY_LEFT)
#define KEY_UD (KEY_UP | KEY_DOWN)

/* Key-press inline functions */

INLINE int combo_pressed (u16 combo)
{
    return (__key_curr & combo) == combo;
}

INLINE int diagonals_pressed()
{
    return (combo_pressed(KEY_UR) || combo_pressed(KEY_UL) ||
        combo_pressed(KEY_DR) || combo_pressed(KEY_DL));
}

INLINE int opposites_pressed()
{
    return (combo_pressed(KEY_UD) || combo_pressed(KEY_RL));
}

#endif

