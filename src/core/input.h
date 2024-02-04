#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H


#ifdef TARGET_3DS
    #include <3ds.h>

#elif TARGET_SDL
    #include <SDL/SDL.h>

#elif TARGET_SDL2
    #include <SDL2/SDL.h>

#elif TARGET_PSVITA
    #include <psp2/ctrl.h>

#else
    #define _CRT_SECURE_NO_WARNINGS

#endif


#include <stdio.h>
#include <time.h>

#include "keys.h"

#include "../utils/list.h"


typedef enum EInputType {
    INP_TYPE_KEYB,
    INP_TYPE_MOUSE,
    INP_TYPE_JOY,
    INP_TYPE_TOUCH
} EInputType;

typedef enum EMouseButton {
    MOUSE_BTN_LEFT,
	MOUSE_BTN_MIDDLE,
	MOUSE_BTN_RIGHT,
	MOUSE_BTN_UNKNOWN
} EMouseButton;

typedef enum EMouseEventType {
	MOUSE_EVT_MOTION,
	MOUSE_EVT_BTN_UP,
	MOUSE_EVT_BTN_DOWN
} EMouseEventType;

typedef enum EJoyEventType {
	JOY_EVT_AXIS_MOVED,
	JOY_EVT_BTN_UP,
	JOY_EVT_BTN_DOWN,
} EJoyEventType;

typedef struct KeyEvent {
    EKey key;
    uint scancode;
}  KeyEvent;

typedef struct MouseEvent {
	EMouseEventType type;
    EMouseButton btn;
    uint btnId;
    vect2d position;
} MouseEvent;

typedef struct JoyEvent {
	EJoyEventType type;
    EJoyButton btn;
    uint btnId;
    vect2d position;
} JoyEvent;

typedef struct InputEvent {
	EInputType type;
    uint time;
    union {
        MouseEvent mouseEvt;
        KeyEvent keyEvt;
        JoyEvent joyEvt;
    };
} InputEvent;

typedef struct InputSystem {
    vect2d vCurrMousePos;
    List activeInputsList;
} InputSystem;


#include "input.h"


void inp_init_input_system(InputSystem* pInputSys);
bool inp_is_key_pressed(InputSystem* pInputSys, EKey key);
bool inp_is_any_key_pressed(InputSystem* pInputSys);
bool inp_is_joy_btn_pressed(EJoyButton joyBtn);
bool inp_is_button_pressed(InputSystem* pInputSys, EMouseButton btn);
bool inp_do_mouse_moved(InputSystem* pInputSys, vect2df* vDest);
MouseEvent* inp_get_button_pressed_event(InputSystem* pInputSys, EMouseButton btn);
bool inp_retrieve_touch(vect2d* touch, int touchSurfaceId);
vect2d inp_get_curr_input_pos(InputSystem* pInputSys);
void inp_display_keys(InputSystem* pInputSys);

#if TARGET_SDL || TARGET_SDL2
    void inp_register_key_event(InputSystem* pInputSys, uint32 eventType, SDL_Keysym key);
    void inp_register_mouse_event(InputSystem* pInputSys, uint32 eventType, vect2d mousePos, uint8 mouseBtn);
#endif

void inp_update_events(InputSystem* inputSys);

void inp_flush_input_events();


#endif
