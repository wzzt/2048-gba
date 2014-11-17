/*
 * 2048.gba: A 2048 clone for the GBA. Quite simple, really
 */

#include "gba.h"
#include "gfx.h"
#include "2048.h"
#include "2048_keys.h"
#include "2048_gfx.h"

/* Note: field values are internally stored as val = 0, 1, 2, ...
 * and externally displayed as blank or 2 to the val'th power */
s32 field[SLOTS];

/* For shuffling and drawing field indexes */
s32 deck[SLOTS];

s32 score;
s32 high_score = 0;

/* Shows title screen */
void title_screen()
{
    int i = 0;
    fill_screen(CLR_BGCOLOR);
    vid_vsync();
    draw_bmp(title_logo, TITLE_LOGO_X, TITLE_LOGO_Y);
    vid_vsync();
    draw_bmp(title_start, TITLE_START_X, TITLE_START_Y);
    draw_bmp(title_score, TITLE_BOX_X, TITLE_BOX_Y  );
    draw_digits(high_score, TITLE_SCORE_X, TITLE_SCORE_Y);
    /* Increment the initial seed each frame, adding any key input as well */
    while ( !(~REG_KEYINPUT & (KEY_START|KEY_A) ) ) {
        i += ~REG_KEYINPUT + 1;
        vid_vsync();
    }
    srandf(i + randf());
}

/* Zeroes the score, empties the field,
 * and creates a fresh deck to draw numbers from */
void init_game()
{
    int i;
    score = 0;
    for (i = 0; i < SLOTS; i++) {
        field[i] = 0;
        deck[i] = i;
    }
    init_game_screen();
}

/* Inserts a new tile into the field before each turn */
void insert_tile()
{
    int i;
    shuffle_deck();
    for (i = 0; i < SLOTS; ++i)
        if (!field[deck[i]]) {
            /* A 4 tile is inserted instead of a 2 tile with a PROB_4 / 255
             * chance */
            field[deck[i]] = (randf() & 0xFF) < PROB_4 ? 2 : 1;
            draw_tile(deck[i], field[deck[i]]);
            return;
        }
}

/* Checks whether the game is still going,
 * allows the player to make a move if so */
int perform_turn()
{
    if (game_status() == LOSS)
        return LOSS;
    /* Keeps track in order to detect duplicate moves from the same keypress */
    static int last_dir;
    int dir;
    dir = NONE;
    do {
        vid_vsync();
        key_poll();
        if (key_pressed(KEY_START)) {
            if (pause_game() == RESTART)
                return RESTART;
        }
        if (opposites_pressed()) /* Also protects against 3+ D-pad presses */
            continue;
        else if (last_dir != get_dir()) /* Ignore holds */
            last_dir = dir = get_dir();
    } while (dir == NONE || !move_field(dir));
    return ONGOING;
}

/* Pauses the game until SELECT resets or START resumes */
int pause_game()
{
    int i;
    vid_vsync();
    draw_bmp(f_pause_box, F_PAUSE_BOX_X, F_PAUSE_BOX_Y);
    draw_bmp(f_pause_msg, F_PAUSE_MSG_X, F_PAUSE_MSG_Y);
    do {
        vid_vsync();
        key_poll();
        if (key_pressed(KEY_SELECT)) return RESTART;
    } while (!key_pressed(KEY_START));
    draw_bmp(f_box, F_BOX_X, F_BOX_Y);  vid_vsync();
    draw_bmp(f_logo, F_LOGO_X, F_LOGO_Y);
    for (i = 0; i < SLOTS; i++)
        draw_tile(i, field[i]);
    return ONGOING;
}

/* Ends the game and shows appropriate screen based on the circumstances */
void game_over(int result)
{
    if (result == RESTART) {
        title_screen();
        return;
    }
    if (result == WIN)
        draw_bmp(f_win_box, F_WIN_BOX_X, F_WIN_BOX_Y);
    else
        draw_bmp(f_gameover_box, F_GAMEOVER_BOX_X, F_GAMEOVER_BOX_Y);
    do {
        key_poll();
        vid_vsync();
    } while ( !( __key_curr & (KEY_START|KEY_A) ) );
}

int main()
{
    int result;
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
    title_screen();
    while (1) {
        init_game();
        do {
            insert_tile();
            result = perform_turn();
        } while (result == ONGOING);
        game_over(result);
    }
    return 0;
}

