/*
 * Definitions and static inline funcs for
 * displaying 2048.gba's graphical assets
 */

#ifndef _2048_GFX_H_
#define _2048_GFX_H_

#include "gba.h"
#include "gfx.h"

/*
 * Graphical assets
 */

extern const u16 f_best_box[];
extern const u16 f_box[];
extern const u16 f_gameover_box[];
extern const u16 f_logo[];
extern const u16 f_pause_box[];
extern const u16 f_pause_msg[];
extern const u16 f_score_box[];
extern const u16 f_win_box[];
extern const u16 num[10][90];
extern const u16 tile[12][1298];
extern const u16 title_logo[];
extern const u16 title_score[];
extern const u16 title_start[];

/*
 * X, Y offsets for graphical assets
 */

/* Title assets */
#define TITLE_LOGO_X 47
#define TITLE_LOGO_Y 20
#define TITLE_START_X 38
#define TITLE_START_Y 92
#define TITLE_BOX_X 71
#define TITLE_BOX_Y 127

/* Coord of top-left corner of rightmost digit */
#define TITLE_SCORE_X 155
#define TITLE_SCORE_Y 133

/* In-game assets */
#define F_PAUSE_BOX_X 6
#define F_PAUSE_BOX_Y 6
#define F_PAUSE_MSG_X 162
#define F_PAUSE_MSG_Y 50
#define F_GAMEOVER_BOX_X 6
#define F_GAMEOVER_BOX_Y 6
#define F_WIN_BOX_X 160
#define F_WIN_BOX_Y 50
#define F_LOGO_X 160
#define F_LOGO_Y 50
#define F_SCORE_BOX_X 166
#define F_SCORE_BOX_Y 112
#define F_BEST_BOX_X 166
#define F_BEST_BOX_Y 10

/* Coordinate of top-left corner of rightmost digit */
#define F_SCORE_X 213
#define F_SCORE_Y 133
#define F_BEST_X 213
#define F_BEST_Y 31

/* field border coordinates */
#define F_BOX_X 6
#define F_BOX_Y 6

#define F_INBOX_X 8
#define F_INBOX_Y 8

/* Slot coordinatess relative to F_INBOX (inner field box) */
#define C1_X_OFF 0
#define R1_Y_OFF 0
#define C2_X_OFF 36
#define R2_Y_OFF 36
#define C3_X_OFF 72
#define R3_Y_OFF 72
#define C4_X_OFF 108
#define R4_Y_OFF 108
extern const int offsets[16][2];

/* Draws a field tile based on slot and value */
INLINE void draw_tile(int slot, int val)
{
    draw_bmp(tile[val], F_INBOX_X + offsets[slot][0], F_INBOX_Y + offsets[slot][1]);
}

void init_game_screen();
void draw_digits(s32 n, int x, int y);

#endif

