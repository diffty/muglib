#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include "types.h"


typedef struct drawbuffer {
    uint8* buffer;
    int width;
    int height;
	int colorDepth;
    int reverse;
    int mutex;

} drawbuffer;


typedef struct GraphicsSystem {
    rect drawBufBlitRect;
    rect screenBufBlitRect;

    #if TARGET_SDL2
        SDL_Window* window;
    #endif

    #if TARGET_SDL || TARGET_SDL2
        SDL_Surface* windowSurface;
    #endif

    drawbuffer framebuffer[1];
} GraphicsSystem;


void gfx_init_graphics_system(GraphicsSystem* pGfxSys);
void gfx_init_window(GraphicsSystem* pGfxSys);
void gfx_fill_with_color(drawbuffer* fb, uint8 colorHex);
void gfx_set_double_buffering(bool isActive);
void gfx_flush_buffer();
void gfx_swap_buffer();
void gfx_wait_for_blank();
void gfx_exit();

#if TARGET_SDL2
SDL_Window* gfx_get_window(GraphicsSystem* pGfxSys);
#endif

#if TARGET_SDL || TARGET_SDL2
SDL_Surface* gfx_get_window_surface(GraphicsSystem* pGfxSys);
#endif

#endif
