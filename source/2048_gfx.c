/*
 * Misc. functions and variable for displaying 2048.gba's graphical assets
 */

#include "gba.h"
#include "gfx.h"
#include "2048.h"
#include "2048_gfx.h"

void init_game_screen()
{
    int i;
    fill_screen(CLR_BGCOLOR); vid_vsync();
    draw_bmp(f_box, F_BOX_X, F_BOX_Y); vid_vsync();
    draw_bmp(f_score_box,   F_SCORE_BOX_X,  F_SCORE_BOX_Y); vid_vsync();
    draw_bmp(f_best_box,    F_BEST_BOX_X,   F_BEST_BOX_Y);  vid_vsync();
    draw_bmp(f_logo,        F_LOGO_X,       F_LOGO_Y    );  vid_vsync();
    draw_digits(score, F_SCORE_X, F_SCORE_Y);
    draw_digits(high_score, F_BEST_X, F_BEST_Y);
    for (i = 0; i < SLOTS; ++i) {
        draw_tile(i, field[i]);
        vid_vsync();
    }
}

/* Draws digits using num[0..9][], right-justified */
void draw_digits(s32 n, int x, int y)
{
    if (n == 0) {
        draw_bmp(num[0], x, y);
        return;
    }
    if (n < 0)
        n = -n;
    int i;
    s32 digits[10];
    for (i = 0; n; i++) {
        digits[i] = n % 10;
        n /= 10;
    }
    x -= num[0][0] * (i - 1);
    while (--i >= 0) {
        draw_bmp(num[digits[i]], x, y);
        x += num[0][0];
    }
}

/* Field tile offsets relative to F_INBOX (inner field box) */
const int offsets[16][2] = {
        {C1_X_OFF, R1_Y_OFF}, {C2_X_OFF, R1_Y_OFF}, {C3_X_OFF, R1_Y_OFF}, {C4_X_OFF, R1_Y_OFF},
        {C1_X_OFF, R2_Y_OFF}, {C2_X_OFF, R2_Y_OFF}, {C3_X_OFF, R2_Y_OFF}, {C4_X_OFF, R2_Y_OFF},
        {C1_X_OFF, R3_Y_OFF}, {C2_X_OFF, R3_Y_OFF}, {C3_X_OFF, R3_Y_OFF}, {C4_X_OFF, R3_Y_OFF},
        {C1_X_OFF, R4_Y_OFF}, {C2_X_OFF, R4_Y_OFF}, {C3_X_OFF, R4_Y_OFF}, {C4_X_OFF, R4_Y_OFF}
};

