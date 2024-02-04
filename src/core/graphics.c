#include "graphics.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../graphics/drawing.h"
#include "constants.h"
#include "system.h"

#ifdef TARGET_PSVITA
    #include <psp2/display.h>
    #include <psp2/kernel/sysmem.h>
    #include <psp2/kernel/threadmgr.h>
#endif

#if TARGET_SDL || TARGET_SDL2
    #include "SDL_rect.h"
#endif

// Hack because there's missing symbols in SDL1.2 derp
#if (TARGET_SDL || TARGET_SDL2) && _MSC_VER > 1700
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
#endif



void gfx_create_display_drawbuffer(drawbuffer* framebuffer) {
    framebuffer->width = SCREEN_WIDTH;
    framebuffer->height = SCREEN_HEIGHT;
    framebuffer->colorDepth = SCREEN_BPP;

    #ifdef TARGET_PSVITA
        framebuffer->mutex = sceKernelCreateMutex("log_mutex", 0, 0, NULL);

        SceUID displayblock = sceKernelAllocMemBlock("display",
                                                    SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
                                                    // looks like vita buffer size must be 256KB aligned (source: debugScreen.c)
                                                    (2 * 1024 * 1024),  
                                                    NULL);

        sceKernelGetMemBlockBase(displayblock, (void**) &framebuffer->buffer);

        framebuffer->platformFrameBuffer = (SceDisplayFrameBuf) {
            sizeof(SceDisplayFrameBuf),
            framebuffer->buffer,
            framebuffer->width,     // this parameter is for real memory framebuffer size
            0,
            framebuffer->width,
            framebuffer->height
        };
    #endif
}


void gfx_init_graphics_system(GraphicsSystem* pGfxSys) {
    pGfxSys->drawBufBlitRect.x = 0;
    pGfxSys->drawBufBlitRect.y = 0;
    pGfxSys->drawBufBlitRect.w = SCREEN_WIDTH;
    pGfxSys->drawBufBlitRect.h = SCREEN_HEIGHT;

    pGfxSys->screenBufBlitRect.x = 0;
    pGfxSys->screenBufBlitRect.y = 0;
    pGfxSys->screenBufBlitRect.w = SCREEN_WIDTH * SCREEN_SCALE;
    pGfxSys->screenBufBlitRect.h = SCREEN_HEIGHT * SCREEN_SCALE;

    pGfxSys->framebuffer = (drawbuffer*) malloc(2 * sizeof(drawbuffer));

    gfx_create_display_drawbuffer(&pGfxSys->framebuffer[0]);
    gfx_create_display_drawbuffer(&pGfxSys->framebuffer[1]);

    pGfxSys->currFrontbufferIdx = 1;
    pGfxSys->currBackbufferIdx = 0;


    #ifdef TARGET_3DS
        gfxInitDefault();
        pGfxSys->framebuffer[0].buffer = gfxGetFramebuffer(GFX_BOTTOM,
                                                           GFX_LEFT,
                                                           NULL,
                                                           NULL);

    #elif TARGET_SDL || TARGET_SDL2
        pGfxSys->pSDLDrawSurface = SDL_CreateRGBSurface(0,
                                                        SCREEN_WIDTH,
                                                        SCREEN_HEIGHT,
                                                        32,
                                                        0,0,0,0);

        pGfxSys->pSDLWindowSurface = gfx_get_window_surface(pGfxSys);

        pGfxSys->framebuffer[0].buffer = (uint8*) pGfxSys->pSDLDrawSurface->pixels;
        pGfxSys->framebuffer[0].reverse = true;
    
    #elif TARGET_PSVITA
        int ret;
        if (ret = sceDisplaySetFrameBuf(&pGfxSys->framebuffer[pGfxSys->currBackbufferIdx].platformFrameBuffer,
                                        SCE_DISPLAY_SETBUF_NEXTFRAME) < 0) {

            printf("Can't set framebuffer. sceDisplaySetFrameBuf returned %d.", ret);
        }
    
    #endif
}

void gfx_swap_buffers(GraphicsSystem* pGfxSys) {
    #if TARGET_PSVITA        
        pGfxSys->currFrontbufferIdx = (pGfxSys->currFrontbufferIdx + 1) % 2;
        pGfxSys->currBackbufferIdx = (pGfxSys->currBackbufferIdx + 1) % 2;

        int ret;
        if (ret = sceDisplaySetFrameBuf(&pGfxSys->framebuffer[pGfxSys->currFrontbufferIdx].platformFrameBuffer,
                                        SCE_DISPLAY_SETBUF_NEXTFRAME) < 0) {

            psvDebugScreenPrintf("Can't set framebuffer. sceDisplaySetFrameBuf returned %d.", ret);
        }
    #endif
}

void gfx_init_window(GraphicsSystem* pGfxSys) {
    #if TARGET_SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        }
        else {
            pGfxSys->pWindowSurface = SDL_SetVideoMode(
                SCREEN_WIDTH * SCREEN_SCALE,
                SCREEN_HEIGHT * SCREEN_SCALE,
                32,
                SDL_SWSURFACE
            );

            if (pGfxSys->pWindowSurface == NULL) {
                printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            }
        }

    #elif TARGET_SDL2
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        }
        else {
            pGfxSys->window = SDL_CreateWindow("Hyper Drift Mayor",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SCREEN_WIDTH * SCREEN_SCALE,
                                        SCREEN_HEIGHT * SCREEN_SCALE,
                                        SDL_WINDOW_SHOWN);
            
            if (pGfxSys->window == NULL) {
                printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            }

            pGfxSys->pSDLWindowSurface = SDL_GetWindowSurface(pGfxSys->window);
        }

    #endif
}

void gfx_fill_with_color(drawbuffer* fb, uint8 colorHex) {
    memset(fb->buffer,
		colorHex,
		fb->colorDepth * SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint8)
	);
}

void gfx_set_double_buffering(bool isActive) {
    #ifdef TARGET_3DS
        gfxSetDoubleBuffering(GFX_BOTTOM, isActive);

    #endif
}

void gfx_flush_buffer() {
    #ifdef TARGET_3DS
        gfxFlushBuffers();

    #endif
}

void gfx_swap_buffer(GraphicsSystem* pGfxSys) {
    #ifdef TARGET_3DS
        gfxSwapBuffers();

    #elif TARGET_SDL
        // SDL_BlitSurface(m_pSDLDrawSurface, &m_drawBufBlitRect, m_pSDLScreenSurface, &m_screenBufBlitRect);
        blit_scaled(m_pSDLDrawSurface, m_pSDLScreenSurface);
        SDL_Flip(m_pSDLScreenSurface);

    #elif TARGET_SDL2
        SDL_Rect drawBufBlitRect = {pGfxSys->drawBufBlitRect.x, pGfxSys->drawBufBlitRect.y, pGfxSys->drawBufBlitRect.w, pGfxSys->drawBufBlitRect.h};
        SDL_Rect screenBufBlitRect = {pGfxSys->screenBufBlitRect.x, pGfxSys->screenBufBlitRect.y, pGfxSys->screenBufBlitRect.w, pGfxSys->screenBufBlitRect.h};

        SDL_BlitScaled(pGfxSys->pSDLDrawSurface, &drawBufBlitRect, pGfxSys->pSDLWindowSurface, &screenBufBlitRect);
        SDL_UpdateWindowSurface(gfx_get_window(pGfxSys));
    #endif
}

void gfx_wait_for_blank() {
    #ifdef TARGET_3DS
        gspWaitForVBlank();
    
    #elif TARGET_PSVITA
        sceDisplayWaitVblankStart();

    #endif
}

void gfx_exit(GraphicsSystem* pGfxSys) {
    #ifdef TARGET_3DS
        gfxExit();

    #elif TARGET_SDL || TARGET_SDL2
        SDL_FreeSurface(pGfxSys->pSDLDrawSurface);

    #endif
}

#if TARGET_SDL2
SDL_Window* gfx_get_window(GraphicsSystem* pGfxSys) {
	return pGfxSys->window;
}
#endif

#if TARGET_SDL || TARGET_SDL2
SDL_Surface* gfx_get_window_surface(GraphicsSystem* pGfxSys) {
	return pGfxSys->pSDLWindowSurface;
}
#endif

#if TARGET_SDL
    // TODO: mettre autre part
    void blit_scaled(SDL_Surface* src, SDL_Surface* dst) {
        int srcW = src->w;
        int srcH = src->h;
        int dstW = dst->w;
        int dstH = dst->h;

        int srcBufSize = srcW * srcH;
        int dstBufSize = dstW * dstH;
        int scaleRatio = dstW / srcW;

        int bpp = src->format->BytesPerPixel;

        for (int i = srcBufSize - 1; i >= 0; i--) {
            for (int j = 0; j < scaleRatio; j++)
                memcpy(((Uint32*) dst->pixels + i * scaleRatio + j), ((Uint32*)src->pixels + i), src->format->BytesPerPixel);
        }

        for (int y = srcH - 1; y >= 0; y--) {
            for (int j = 0; j < scaleRatio; j++)
            memcpy(((Uint32*) dst->pixels + dst->w * (y * scaleRatio + j)), ((Uint32*)dst->pixels + dst->w * y), dst->pitch);
        }
    }
#endif
