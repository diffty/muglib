#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "core/system.h"
#include "core/graphics.h"
#include "platform/defines.h"
#include "core/input.h"


#define NET_PARAM_MEM_SIZE (1*1024*1024)


int main(int argc, char *argv[]) {
    System mainSys;
    GraphicsSystem gfxSys;
    
    sys_init_system(&mainSys);
    sys_init_console();

    gfx_init_graphics_system(&gfxSys);
    inp_init_input_system(&mainSys.inputSys);
    
    while (sys_main_loop(&mainSys)) {
        
    }

    return 0;
}
