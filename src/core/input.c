#include "input.h"

#ifdef TARGET_PSVITA
    #include <psp2/ctrl.h>
    #include <psp2/touch.h>

#endif


void inp_init_input_system(InputSystem* pInputSys) {
    pInputSys->activeInputsList = List(InputEvent);

    #ifdef TARGET_PSVITA
        // Initializing touch screens and analogs
        sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);
        sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
        sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);
        
        // Enable analog sampling
        sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
    #endif
}

bool inp_is_key_pressed(InputSystem* pInputSys, EKey key) {
    // TODO: REWRITE THIS
    /*
    LLNode* currNode = pInputSys->currInputList.pHead;
    KeyEvent* currKey;

    while (currNode != NULL) {
        currKey = (KeyEvent*) currNode->pData;
        if (currKey->key == key) return true;
        currNode = currNode->pNext;
    }
    */

    return false;
}

bool inp_is_any_key_pressed(InputSystem* pInputSys) {
    if (pInputSys->activeInputsList.count > 0)
        return true;
    else
        return false;
}

bool inp_is_joy_btn_pressed(EJoyButton joyBtn) {
    #ifdef TARGET_3DS
        return hidKeysHeld() & get_platform_joy_button_code(joyBtn);

    #elif TARGET_PSVITA
        SceCtrlData ctrl;
        sceCtrlPeekBufferPositive(0, &ctrl, 1);
        return ctrl.buttons & get_platform_joy_button_code(joyBtn);

    #else
        return false;

    #endif
}

bool inp_is_button_pressed(InputSystem* pInputSys, EMouseButton btn) {
    // TODO: REWRITE THIS
    /*
    LLNode* currNode = pInputSys->currMouseList.pHead;
    MouseEvent* currMouseBtn;

    while (currNode != NULL) {
        currMouseBtn = (MouseEvent*)currNode->pData;
        if (currMouseBtn->btn == btn) return true;
        currNode = currNode->pNext;
    }

    return false;
    */
}

bool inp_do_mouse_moved(InputSystem* pInputSys, vect2df* vDest) {
    // REWRITE THIS
    /*
    LLNode* currNode = pInputSys->currMouseList.pHead;
    
    while (currNode != NULL) {
        MouseEvent* currEvent = (MouseEvent*)currNode->pData;

        if (currEvent->type == MOUSE_EVT_MOTION) {
            printf("test");
            return true;
        }

        currNode = currNode->pNext;
    }

    return false;
    */
}

MouseEvent* inp_get_button_pressed_event(InputSystem* pInputSys, EMouseButton btn) {
    // TODO: REWRITE THIS
    /*
    LLNode* currNode = pInputSys->currMouseList.pHead;
    MouseEvent* currMouseBtn;

    while (currNode != NULL) {
        currMouseBtn = (MouseEvent*)currNode->pData;
        if (currMouseBtn->btn == btn) return currMouseBtn;
        currNode = currNode->pNext;
    }

    return NULL;
    */
}

bool inp_retrieve_touch(vect2d* touch, int touchSurfaceId) {
    #ifdef TARGET_3DS
        touchPosition tp;
        hidTouchRead(&tp);

        if (tp.px + tp.py > 0) {
            vect2d touchPt;

            touch->x = tp.px;
            touch->y = tp.py;

            return true;
        }
        else {
            return false;
        }

    #else
        return false;

    #endif
}

vect2d inp_get_curr_input_pos(InputSystem* pInputSys) {
    return pInputSys->vCurrMousePos;
}

void inp_display_keys(InputSystem* pInputSys) {
    int i;

    printf("%d ", pInputSys->activeInputsList.count);

    for (i = 0; i < pInputSys->activeInputsList.count; i++) {
        InputEvent* currInputEvt = (InputEvent*)lst_get(&pInputSys->activeInputsList, i);
        printf("%u ", currInputEvt->keyEvt.scancode);
    }

    printf("\n");
}

#if TARGET_SDL || TARGET_SDL2
void inp_register_key_event(InputSystem* pInputSys, uint32 eventType, SDL_Keysym key) {
    
}

void inp_register_mouse_event(InputSystem* pInputSys, uint32 eventType, vect2d mousePos, uint8 mouseBtn) {
    
}
#endif

void inp_update_events(InputSystem* inputSys) {
    
}

void inp_flush_input_events() {

}
