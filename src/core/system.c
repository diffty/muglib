#include "system.h"
#include "input.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef TARGET_3DS
    #include <3ds.h>
#endif

#ifdef TARGET_SDL2
    #include <SDL2/SDL.h>
#endif

#ifdef TARGET_WIN
    #include <Windows.h>
#endif

#ifdef TARGET_OSX
    #include <mach/clock.h>
    #include <mach/mach.h>
    #include <time.h>
    #include <unistd.h>
#endif

#ifdef TARGET_PSVITA
    #define NO_psvDebugScreenInit
    #include "../platform/psvita/console/debugScreen.h"

#endif


static System sys_instance;

System* sys_get_system_instance() {
    return &sys_instance;
}

void sys_init_system(System* pSystem) {
    pSystem->isMainLoopRunning = 1;
    pSystem->loggersList = List(Logger*);
	sys_init_main_loop(pSystem);
    inp_init_input_system(&pSystem->inputSys);
}

void sys_init_main_loop(System* pSystem) {
	pSystem->startLoopTime = get_current_time();
	pSystem->prevLoopTime = pSystem->startLoopTime;
	pSystem->deltaTime = pSystem->startLoopTime - pSystem->prevLoopTime;
}

void sys_add_logger(System* pSystem, Logger* logger) {
    lst_append(&pSystem->loggersList, &logger);
}

void sys_log_to_all_adapters(System* pSystem, char* s) {    
    LogRecord newLogRecord;
    newLogRecord.time = time(NULL);
    newLogRecord.severity = ELogSeverity_DEBUG;
    newLogRecord.message = malloc(strlen(s));
    strcpy(newLogRecord.message, s);

    int i;
    for (i = 0; i < pSystem->loggersList.count; i++) {
        Logger* currLogger = *((Logger**) lst_get(&pSystem->loggersList, i));
        log_logger_write_logrecord(currLogger, &newLogRecord);
    }

    free(newLogRecord.message);
}

void sys_init_console() {
    #if TARGET_3DS
	    consoleInit(GFX_TOP, NULL);
	
    #elif TARGET_SDL || TARGET_SDL2
        /*AllocConsole();
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);*/

    #elif TARGET_PSVITA
        // Initialize debug screen
        psvDebugScreenInit();
        psvDebugScreenSetFont(psvDebugScreenScaleFont2x(psvDebugScreenGetFont()));

    #endif
}

void sys_quit_loop(System* pSystem) {
	pSystem->isMainLoopRunning = 0;
}

void sys_exit(System* pSystem) {
    #if TARGET_SDL
        SDL_Quit();

    #elif TARGET_SDL2
        SDL_DestroyWindow(pSystem->window);
        SDL_Quit();

    #endif
}

void sys_sleep(unsigned int uSleepTime) {
    #if TARGET_WIN
        HANDLE timer;
        LARGE_INTEGER ft;

        ft.QuadPart = -(10 * (__int64) uSleepTime);

        timer = CreateWaitableTimer(NULL, TRUE, NULL);
        SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
        WaitForSingleObject(timer, INFINITE);
        CloseHandle(timer);

    #elif TARGET_MAC
        usleep(uSleepTime);

    #endif
}

int sys_main_loop(System* pSystem) {
	pSystem->startLoopTime = get_current_time();
    //psvDebugScreenPrintf("%lf %lf\n", pSystem->startLoopTime, get_current_time());
	pSystem->deltaTime = pSystem->startLoopTime - pSystem->prevLoopTime;
	pSystem->prevLoopTime = pSystem->startLoopTime;

    #ifdef TARGET_3DS
        hidScanInput();
        return aptMainLoop();

    #elif TARGET_SDL || TARGET_SDL2
        /*SDL_Event sdlEvent;

        while (SDL_PollEvent(&sdlEvent) != 0) {
            if (sdlEvent.type == SDL_QUIT) {
                pSystem->bIsMainLoopRunning = false;
            }

            else if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP) {
                pSystem->inputSys.RegisterKeyEvent(sdlEvent.type, sdlEvent.key.keysym);
            }

            else if (sdlEvent.type == SDL_MOUSEMOTION || sdlEvent.type == SDL_MOUSEBUTTONDOWN || sdlEvent.type == SDL_MOUSEBUTTONUP) {
                vect2d_t mousePos;
                int x, y;
                
                SDL_GetMouseState(&x, &y);
                mousePos.x = x;
                mousePos.y = y;

                pSystem->inputSys.RegisterMouseEvent(sdlEvent.type, mousePos, sdlEvent.button.button);
            }
        }*/

        return pSystem->isMainLoopRunning;

    #else
        return pSystem->isMainLoopRunning;

    #endif
}

InputSystem* sys_get_input_system(System* pSystem) {
	return &pSystem->inputSys;
}

double sys_get_delta_time(System* pSystem) {
	return pSystem->deltaTime;
}
