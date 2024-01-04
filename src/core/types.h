#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


// Platform-specific type defines
#ifdef TARGET_3DS
    #include <3ds.h>
    
    typedef u8 uint8;
    typedef u32 uint32;

#else
    #if !TARGET_SDL && !TARGET_SDL2 && !TARGET_PSVITA
        typedef unsigned char uint8_t;

        #if ULONG_MAX == 0xffffffff
            typedef long int32_t;
            typedef unsigned long uint32_t;

        #elif UINT_MAX == 0xffffffff
            typedef int int32_t;
            typedef unsigned int uint32_t;

        #endif

    #else
        #ifdef TARGET_SDL
            #include <SDL/SDL.h>
            #define SDL_Keysym SDL_keysym

        #elif TARGET_SDL2
            #include <SDL2/SDL.h>

        #endif

    #endif

    typedef uint8_t uint8;
    typedef uint32_t uint32;

#endif

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int uint;

typedef struct vect2d {
	long x;
	long y;
} vect2d;

typedef struct vect2df {
	float x;
	float y;
} vect2df;

typedef struct size2d {
	long w;
	long h;
} size2d;

typedef struct size2df {
	float w;
	float h;
} size2df;

typedef struct color3 {
	unsigned int r;
	unsigned int g;
	unsigned int b;
} color3;

typedef struct color4 {
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;
} color4;

typedef struct quad2d {
    vect2d tl;
    vect2d tr;
    vect2d bl;
    vect2d br;
} quad2d;

typedef struct quad2df {
    vect2df tl;
    vect2df tr;
    vect2df bl;
    vect2df br;
} quad2df;

typedef struct rect {
    long x;
    long y;
    long w;
    long h;
} rect;

typedef struct rectf {
    float x;
    float y;
    float w;
    float h;
} rectf;

typedef int bool;
#define true 1
#define false 0

#endif
