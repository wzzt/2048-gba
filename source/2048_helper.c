/*
 * Functions used by the major functions contained in 2048.c
 */

#include "gba.h"
#include "gfx.h"
#include "2048.h"
#include "2048_keys.h"
#include "2048_gfx.h"

/* Fisher-Yates shuffle for use in picking slots to insert new tiles */
void shuffle_deck()
{
    int i, r, temp;
    for (i = 0; i < SLOTS; i++) {
        r = (randf() % (SLOTS - i)) + i;
        temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }
}

/* 
 * The 2-D representation of the in-game field looks like this:
 *
 *    0  1  2  3
 *    4  5  6  7
 *    8  9 10 11
 *   12 13 14 15
 *
 * movedirs[][][] determines how the tiles are pushed around when a
 * move occurs.
 * 
 * The respective directions for the first dimension of this array are:
 *   UP, LEFT, RIGHT, DOWN
 *
 * The tiles are pushed from right to left in array order, so if you were
 * moving UP, the tiles in the first column would be pushed ilke this:
 *   0 <- 4 <- 8 <- 12
 */

const int movedirs[4][4][4] =
{
        { {0, 4, 8, 12}, {1, 5, 9, 13}, {2, 6, 10, 14}, {3, 7, 11, 15} },
        { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15} },
        { {15, 14, 13, 12}, {11, 10, 9, 8}, {7, 6, 5, 4}, {3, 2, 1, 0} },
        { {12, 8, 4, 0}, {13, 9, 5, 1}, {14, 10, 6, 2}, {15, 11, 7, 3} }
};

/* Checks whether the game is over. The game is ongoing
 * as long as there is at least one empty tile or there
 * are two adjacent tiles with the same value. */
int game_status()
#define FMKIJ(k,i,j) field[movedirs[k][i][j]]
{
    int i, j, k;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            for (k = 0; k <= 1; k++)
                if (!FMKIJ(k, i, j) ||
                        (j < 3 && FMKIJ(k, i, j) == FMKIJ(k, i, j + 1))
                   )
                    return ONGOING;
    return LOSS;
#undef FMKIJ
}

/* Pushes all of the tiles in each row or column in a given direction,
 * returning 1 if the move is valid and 0 otherwise. */
int move_field(int dir)
{
#define SLOTINDEX(x) movedirs[dir][row][x]
#define SLOT(x) field[SLOTINDEX(x)]
    /* The moved flag determines whether the move is valid */
    int row, from, to, i, j, moved_flag;
    s32 temp_slot;
    int temp[4];
    for (row = moved_flag = 0; row < 4; row++) {
        /* Keep track of the original state of the current row/column */
        for (j = 0; j < 4; ++j)
            temp[j] = SLOT(j);
        for (from = to = 0; from < 4; from++) {
             /* If the "from" slot contains a number... */
            if(SLOT(from)) {
                /* Empty the "from" slot */
                temp_slot = SLOT(from);
                SLOT(from) = 0;
                /* If the "to" slot is empty, insert the "from" value */
                if(!SLOT(to))
                    SLOT(to) = temp_slot;
                /* If "from" val == "to" val, merge the "to" and "from" slots */
                else if (SLOT(to) == temp_slot) {
                    /* Adding the displayed sum of the merged tiles together,
                     * so 2**n * 2 */
                    add_score(2 << SLOT(to));
                    SLOT(to)++;
                    to++;
                /* Else, push the "from" value into the next "to" slot */
                } else {
                    to++;
                    SLOT(to) = temp_slot;
                }
            }
            /* if any slots in the row/column have changed, set the moved flag */
            for (j = 0; !moved_flag && j < 4; ++j)
                if (temp[j] != SLOT(j))
                    moved_flag = 1;
        }
    }
    for (i = 0; i < SLOTS; ++i)
        draw_tile(i, field[i]);
    draw_digits(score, F_SCORE_X, F_SCORE_Y);
    if (score > high_score) {
        high_score = score;
        draw_digits(high_score, F_BEST_X, F_BEST_Y);
    }
    return moved_flag;
#undef SLOT
#undef SLOTINDEX
}

