/*
 * Parameters and major function declarations for 2048.gba
 */

#ifndef _2048_H_
#define _2048_H_

#include "gba.h"

#define CLR_BGCOLOR 0x77DE

/* Number of slots on the field (4 x 4 is 16) */
#define SLOTS 16

s32 field[SLOTS];

/* For shuffling and drawing field indexes */
s32 deck[SLOTS];

s32 high_score;
s32 score;

/* Winning value is 1 << n (11 for 2048) */
#define WIN_VAL 11

/* Probability of getting a 4 tile, n / 255 */
#define PROB_4 25

/* Game statuses */
#define ONGOING 0
#define WIN 1
#define LOSS -1
#define RESTART -2

/* Movement directions */
#define NONE    -1
#define UP      0
#define LEFT    1
#define RIGHT   2
#define DOWN    3

/* Info about movedirs is in 2048_helper.c */
extern const int movedirs[4][4][4];

INLINE void add_score(s32 val)
{
    score += val;
}

/* Converts key-presses to directions for move_field() */
INLINE int get_dir()
{
#define KP(x) key_pressed(x)
        return  KP(KEY_UP)    ? UP    : KP(KEY_LEFT) ? LEFT :
                KP(KEY_RIGHT) ? RIGHT : KP(KEY_DOWN) ? DOWN :
                NONE;
#undef KP
}

int game_status();
int move_field(int dir);
int pause_game();
int perform_turn();
void game_over(int result);
void init_game();
void insert_tile();
void shuffle_deck();
void title_screen();

#endif

