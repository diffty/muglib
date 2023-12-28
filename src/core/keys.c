#include "keys.h"


#if TARGET_PSVITA
    #include "../platform/psvita/inputmap.h"

#elif TARGET_SDL2
    #include "../platform/sdl2/inputmap.h"

#elif TARGET_3DS
    #include "../platform/3ds/inputmap.h"

#endif


int get_platform_joy_button_code(EJoy muglibJoyBtnCode) {
    return JOY_BUTTON_MAPPING[muglibJoyBtnCode];
}

// TODO: Pour SDL on va avoir besoinde l'inverse
// (penser : quand on reçoit un event on reçoit un SDLK qu'il faut transformer
// en EKey)
