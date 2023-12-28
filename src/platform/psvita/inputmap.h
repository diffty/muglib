#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef TARGET_PSVITA

#include <psp2/ctrl.h>


int KEYS_MAPPING[113];

int JOY_BUTTON_MAPPING[16] = {
    SCE_CTRL_CIRCLE,
    SCE_CTRL_CROSS,
    SCE_CTRL_TRIANGLE,
    SCE_CTRL_SQUARE,
    
    SCE_CTRL_START,
    SCE_CTRL_SELECT,
    
    SCE_CTRL_LEFT,
    SCE_CTRL_RIGHT,
    SCE_CTRL_UP,
    SCE_CTRL_DOWN,

    SCE_CTRL_L1,
    SCE_CTRL_L2,
    SCE_CTRL_L3,
    SCE_CTRL_R1,
    SCE_CTRL_R2,
    SCE_CTRL_R3,
};

#endif
