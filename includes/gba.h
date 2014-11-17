/* 
 * Definitions and inline functions for GBA functionality
 */

#ifndef _GBA_H_
#define _GBA_H_

/* Typedefs */
typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

typedef volatile s8 vs8;
typedef volatile u8 vu8;
typedef volatile s16 vs16;
typedef volatile u16 vu16;
typedef volatile s32 vs32;
typedef volatile u32 vu32;

#define INLINE static inline

/* Memory map defines */
#define MEM_IO      0x04000000
#define MEM_VRAM    0x06000000
#define vid_mem     ((u16 *) MEM_VRAM)

#define REG_DISPCNT     *((vu32*) (MEM_IO+0x0000))
#define REG_DISPSTAT    *((vu16*) (MEM_IO+0x0004))
#define REG_VCOUNT      *((vu16*) (MEM_IO+0x0006))
#define REG_KEYINPUT    *((vu16*) (MEM_IO+0x0130))

/* Graphics modes */
#define DCNT_MODE0  0x0000
#define DCNT_MODE1  0x0001
#define DCNT_MODE2  0x0002
#define DCNT_MODE3  0x0003
#define DCNT_MODE4  0x0004
#define DCNT_MODE5  0x0005

/* Layers */
#define DCNT_BG0    0x0100
#define DCNT_BG1    0x0200
#define DCNT_BG2    0x0400
#define DCNT_BG3    0x0800
#define DCNT_OBJ    0x1000

/* Video defines */
#define SCREEN_WIDTH    240
#define SCREEN_HEIGHT   160

/* Key defines */
#define KEY_A 0x0001
#define KEY_B 0x0002
#define KEY_SELECT 0x0004
#define KEY_START 0x0008
#define KEY_RIGHT 0x0010
#define KEY_LEFT 0x0020
#define KEY_UP 0x0040
#define KEY_DOWN 0x0080
#define KEY_R 0x0010
#define KEY_L 0x0020
#define KEY_MASK 0x03FF

/* Global variables */
extern s32 __randn;
extern u16 __key_curr;
extern u16 __key_prev;

/* Functions */

INLINE int key_pressed(u16 key)
{
    return (!(__key_prev & key) && (__key_curr & key));
}

INLINE s32 randf() /* range 0-32767 */
{
    __randn = 1664525 * __randn + 1013904223;
    return (__randn >> 16) & 0x7FFF;
}

INLINE void vid_vsync() /* wait 1 frame (1/60 of a second) */
{
        while (REG_VCOUNT >= 160); // wait until VDraw
        while (REG_VCOUNT < 160); // wait until VBlank
}

void key_poll();
s32 srandf(s32 seed);

#endif

