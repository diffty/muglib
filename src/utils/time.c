#include "time.h"

#include <stdlib.h>
#include <stdio.h>

#include "../core/system.h"

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

//#include <time.h>

#ifdef TARGET_OSX
#include <mach/clock.h>
#include <mach/mach.h>
#include <time.h>
#include <unistd.h>
#endif

#ifdef TARGET_PSVITA
#include <time.h>
#include <psp2/rtc.h>
#endif


double get_current_time() {
    #ifdef TARGET_WIN
        System* pSystem = sys_get_system_instance();

        LARGE_INTEGER currTick;
        LARGE_INTEGER t;

        if (QueryPerformanceCounter(&t) != 0)
            currTick.QuadPart = t.QuadPart;

        double test = ((((double) currTick.QuadPart / (double) pSystem->tickFrequency.QuadPart)));
        return test;
        //return (uint32) (currTick.QuadPart / (freq.QuadPart / 1000000));
    
    #elif TARGET_MAC
        timespec timeStruct;
        
        /*#if MAC_OS_X_VERSION_MIN_REQUIRED < 101200
        clock_gettime(CLOCK_REALTIME, &timeStruct);
        #else*/
        clock_serv_t cclock;
        mach_timespec_t machTimeStruct;
        host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
        clock_get_current_time(cclock, &machTimeStruct);
        mach_port_deallocate(mach_task_self(), cclock);
        timeStruct.tv_sec = machTimeStruct.tv_sec;
        timeStruct.tv_nsec = machTimeStruct.tv_nsec;
        /*#endif*/
        
        return ((double) timeStruct.tv_nsec / 1000000000) + timeStruct.tv_sec;

    #elif TARGET_SDL || TARGET_SDL2
	    return SDL_GetTicks();

    #elif TARGET_3DS
        return ((double) osGetTime() / 1000.);

    #elif TARGET_DOS
        double currentTime;
        struct time t_struc;
        gettime(&t_struc);
        currentTime = ((double)time(NULL) + ((double)t_struc.ti_hund)*0.01);
        return currentTime;
    
    #elif TARGET_PSVITA
        SceDateTime dt;

        if (sceRtcGetCurrentClockLocalTime(&dt) < 0) {
            //psvDebugScreenPrintf("Error while retrieving clock!");
            //sceKernelExitProcess(1);
        }

		return ((double) time(NULL) + ((double) dt.microsecond) / 1000000.);
    #endif

    return -1;
}
