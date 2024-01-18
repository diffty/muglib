#ifndef CORE_SYSTEM_H
#define CORE_SYSTEM_H

#include <stdlib.h>
#include <stdio.h>


#ifdef TARGET_3DS
    #include <3ds.h>
#endif

#ifdef TARGET_SDL2
    #include <cstdio>
    #include <SDL2/SDL.h>
#endif

#ifdef TARGET_WIN
    #include <Windows.h>
#endif

#include <time.h>

#ifdef TARGET_OSX
    #include <mach/clock.h>
    #include <mach/mach.h>
    #include <time.h>
    #include <unistd.h>
#endif

#include "input.h"

#include "../logging/adapters/base.h"
#include "../utils/list.h"
#include "../utils/time.h"


typedef struct System {
    int isMainLoopRunning;
    double startLoopTime;
    double prevLoopTime;
    double deltaTime;
    InputSystem inputSys;
    List logAdapterList;

    #if TARGET_WIN
        LARGE_INTEGER tickFrequency;
    #endif

    #if TARGET_SDL2
        SDL_Window* window;
    #endif

    #if TARGET_SDL || TARGET_SDL2
        SDL_Event event;
        SDL_Surface* pWindowSurface;
    #endif

} System;


static System sys_instance;

System* sys_get_system_instance();
InputSystem* sys_get_input_system(System* pSystem);
void sys_init_system(System* pSystem);
void sys_init_console();
void sys_init_window(System* pSystem);
void sys_init_main_loop(System* pSystem);
void sys_add_logger_adapter(System* pSystem, LogAdapter* newLogAdapter);
void sys_log_to_all_adapters(System* pSystem, char* s);
int sys_main_loop(System* pSystem);
void sys_quit_loop(System* pSystem);
double sys_get_delta_time(System* pSystem);
void sys_sleep(unsigned int uSleepTime);
void sys_exit(System* pSystem);

#if TARGET_SDL2
    SDL_Window* sys_get_window(System* pSystem);
#endif

#if TARGET_SDL || TARGET_SDL2
    SDL_Surface* getWindowSurface(System* pSystem);
#endif

#endif