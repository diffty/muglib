#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/core/system.h"

#include <SDL2/SDL.h>


int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); //initalisation du son et de la video

    System mainSys;
    sys_init_system(&mainSys);
    sys_init_main_loop(&mainSys);

    InputSystem inputSys;
    inp_init_input_system(&inputSys);

    return 0;
}
