#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <psp2/sysmodule.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/display.h>

#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/net/http.h>

#include <psp2/io/fcntl.h>

#include <psp2/kernel/threadmgr.h>

#include "core/system.h"
#include "core/graphics.h"
#include "platform/defines.h"
#include "graphics/drawing.h"
#include "core/input.h"

#include "platform/psvita/console/debugScreen.h"
#include "utils/time.h"

#include <time.h>


#define NET_PARAM_MEM_SIZE (1*1024*1024)


int main(int argc, char *argv[]) {
    System mainSys;
    GraphicsSystem gfxSys;
    
    sys_init_system(&mainSys);
    sys_init_console();

    gfx_init_graphics_system(&gfxSys);
    inp_init_input_system(&mainSys.inputSys);
    
    psvDebugScreenUseFramebuffer(gfxSys.framebuffer[0].buffer, gfxSys.framebuffer[0].mutex);

    sceKernelLockMutex(gfxSys.framebuffer[0].mutex, 1, NULL);
    memset(&gfxSys.framebuffer[0].buffer[gfxSys.framebuffer[0].width * 4 * 10],
           0xFF,
           gfxSys.framebuffer[0].width * 4);
    sceKernelUnlockMutex(gfxSys.framebuffer[0].mutex, 1);


    printf("Test\n");


    float x = 0.;
    float y = 0.;
    
    while (sys_main_loop(&mainSys)) {
        sceKernelLockMutex(gfxSys.framebuffer[0].mutex, 1, NULL);
        gfx_fill_with_color(&gfxSys.framebuffer[0], 0x0);
        sceKernelUnlockMutex(gfxSys.framebuffer[0].mutex, 1);
        
        printf("%f\n", mainSys.deltaTime);

        if (inp_is_joy_btn_pressed(JOY_DOWN)) {
            y = y + 50. * mainSys.deltaTime;
        }
        else if (inp_is_joy_btn_pressed(JOY_UP)) {
            y = y - 50. * mainSys.deltaTime;
        }

        if (inp_is_joy_btn_pressed(JOY_LEFT)) {
            x = x - 50. * mainSys.deltaTime;
        }
        else if (inp_is_joy_btn_pressed(JOY_RIGHT)) {
            x = x + 50. * mainSys.deltaTime;
        }

        sceKernelLockMutex(gfxSys.framebuffer[0].mutex, 1, NULL);
        drawBox(&gfxSys.framebuffer[0],
                floor(-10 + x), floor(50 + y), floor(150 + x), floor(150 + y),
                (color4) { 255, 0, 0, 255 });
        sceKernelUnlockMutex(gfxSys.framebuffer[0].mutex, 1);

        sceDisplayWaitVblankStart();
    }



    /* 
    // Initialize Net
    sceSysmoduleLoadModule(SCE_SYSMODULE_NET); // load NET module
    
    int ret = sceNetShowNetstat();
    SceNetInitParam net_init_param; // Net init param structure
    
    if (ret == SCE_NET_ERROR_ENOTINIT) {
        net_init_param.memory = malloc(NET_PARAM_MEM_SIZE);
        net_init_param.size = NET_PARAM_MEM_SIZE;
        net_init_param.flags = 0;
        memset(net_init_param.memory, 0, NET_PARAM_MEM_SIZE);
        ret = sceNetInit(&net_init_param);
        if (ret < 0) printf("An error occurred while starting network.");
    }

    // Init socket connection
    // open a socket to listen for datagrams (i.e. UDP packets) on port 7001
    int32_t sfd = sceNetSocket("osc-destination", SCE_NET_AF_INET, SCE_NET_SOCK_DGRAM, 0);
    if (sfd < 0) {
        printf("Error while creating socket\n");
        sceKernelExitProcess(-1);
        return -1;
    }
    printf("Socket created.\n");


    // Preparing IP destination
    SceNetInAddr dst_addr;			// destination address
    printf("Converting IP address.\n");
    sceNetInetPton(SCE_NET_AF_INET, "192.168.1.47", (void*) &dst_addr);

    // Connecting to UDP server
    SceNetSockaddrIn addrTo; 	// server address to send data to
    memset(&addrTo, 0, sizeof(addrTo));
    addrTo.sin_family = SCE_NET_AF_INET;
    addrTo.sin_addr = dst_addr;
    addrTo.sin_port = sceNetHtons(7001);


    // Initialize NetCtl (for network info retrieving)
    sceNetCtlInit();

    // Network info retrieving
    SceNetCtlInfo vitaNetInfo;
    sceNetCtlInetGetInfo(SCE_NETCTL_INFO_GET_IP_ADDRESS, &vitaNetInfo);
    printf("IP address %s\n", vitaNetInfo.ip_address);
    */


    // Quitting
    sceKernelExitProcess(0);

    return 0;
}
