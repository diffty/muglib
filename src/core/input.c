#include "input.h"

#ifdef TARGET_PSVITA
	#include <psp2/ctrl.h>
	#include <psp2/touch.h>

#endif


void inp_init_input_system(InputSystem* pInputSys) {
	initList(&pInputSys->currEventsList);
	initList(&pInputSys->currInputList);
	initList(&pInputSys->currMouseList);

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
	LLNode* currNode = pInputSys->currInputList.pHead;
	KeyEvent* currKey;

	while (currNode != NULL) {
		currKey = (KeyEvent*) currNode->pData;
		if (currKey->key == key) return true;
		currNode = currNode->pNext;
	}

	return false;
}

bool inp_is_any_key_pressed(InputSystem* pInputSys) {
	if (pInputSys->currInputList.size > 0)
		return true;
	else
		return false;
}

bool inp_is_joy_btn_pressed(EJoy joyBtn) {
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
	LLNode* currNode = pInputSys->currMouseList.pHead;
	MouseEvent* currMouseBtn;

	while (currNode != NULL) {
		currMouseBtn = (MouseEvent*)currNode->pData;
		if (currMouseBtn->btn == btn) return true;
		currNode = currNode->pNext;
	}

	return false;
}

bool inp_do_mouse_moved(InputSystem* pInputSys, vect2df* vDest) {
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
}

MouseEvent* inp_get_button_pressed_event(InputSystem* pInputSys, EMouseButton btn) {
	LLNode* currNode = pInputSys->currMouseList.pHead;
	MouseEvent* currMouseBtn;

	while (currNode != NULL) {
		currMouseBtn = (MouseEvent*)currNode->pData;
		if (currMouseBtn->btn == btn) return currMouseBtn;
		currNode = currNode->pNext;
	}

	return NULL;
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

void inp_display_keys(LinkedList* list) {
	LLNode* currNode = list->pHead;
	KeyEvent* currKey;

	while (currNode != NULL) {
		currKey = (KeyEvent*)currNode->pData;
		printf("%d ", currKey->key);
		currNode = currNode->pNext;
	}
	printf("\n");
}

#if TARGET_SDL || TARGET_SDL2
void inp_register_key_event(InputSystem* pInputSys, uint32 eventType, SDL_Keysym key) {
    KeyEvent* keyEvt = (KeyEvent*) malloc(sizeof(KeyEvent));
    keyEvt->key = convertSDLToMuggineKey(key);

	//InputEvent* evt = new InputEvent;
	//evt->type = IN_KEYB;
	//evt->time = (float)time(NULL);
	//evt->event = &keyEvt;
    
	//LLNode* newInputEvt = new LLNode;
    //newInputEvt->pData = evt;
	//addNodeToList(&currEventsList, newInputEvt);

	KeyEvent* currKey = NULL;

	LLNode* currNode = pInputSys->currInputList.pHead;

	if (eventType == SDL_KEYDOWN) {
		//displayKeys(&pInputSys->currInputList);

		if (IsKeyPressed(keyEvt->key)) {
			free(keyEvt);
		}
		else {
			LLNode* newKey = (LLNode*) malloc(sizeof(LLNode));
			newKey->pData = keyEvt;
			addNodeToList(&pInputSys->currInputList, newKey);
		}
	}
	else if (eventType == SDL_KEYUP) {
		//displayKeys(&pInputSys->currInputList);

		LLNode* prevNode = NULL;
		currNode = pInputSys->currInputList.pHead;

		while (currNode != NULL) {
			currKey = (KeyEvent*) currNode->pData;

			if (currKey->key == keyEvt->key) {
				LLNode* newCurrNode = currNode->pNext;

				if (prevNode != NULL) {
					prevNode->pNext = currNode->pNext;
				}
				else {
					pInputSys->currInputList.pHead = currNode->pNext;
				}

				if (currNode->pNext == NULL) {
					pInputSys->currInputList.pTail = prevNode;
				}

				free(currKey);
				free(currNode);

				currNode = newCurrNode;

				pInputSys->currInputList.size--;
			}
			else {
				prevNode = currNode;
				currNode = currNode->pNext;
			}
		}
	}
}

void inp_register_mouse_event(InputSystem* pInputSys, uint32 eventType, vect2d_t mousePos, uint8 mouseBtn) {
	MouseEvent* mouseEvt = NULL;
	MouseEvent* currMouse = NULL;

	LLNode* currNode = pInputSys->currInputList.pHead;

	mousePos.x /= SCREEN_SCALE;
	mousePos.y /= SCREEN_SCALE;

	pInputSys->vCurrMousePos = mousePos;

	// printf("caca %d\n", mouseBtn);

	// mouseEvt = new MouseEvent;
	// mouseEvt->position = mousePos;

	if (eventType != SDL_MOUSEMOTION) {
		mouseEvt = (MouseEvent*) malloc(sizeof(MouseEvent));
		mouseEvt->position = mousePos;

		if		(mouseBtn == 1) mouseEvt->btn = MOUSE_BTN_LEFT;
		else if (mouseBtn == 2) mouseEvt->btn = MOUSE_BTN_MIDDLE;
		else if (mouseBtn == 3) mouseEvt->btn = MOUSE_BTN_RIGHT;
		else					mouseEvt->btn = MOUSE_BTN_UNKNOWN;
	}
	else {
		// mouseEvt->type = MOUSE_EVT_MOTION;
	}

	if (eventType == SDL_MOUSEBUTTONDOWN) {
		mouseEvt->type = MOUSE_EVT_BTN_DOWN;

		if (IsButtonPressed(mouseEvt->btn)) {
			free(mouseEvt);
		}
		else {
			LLNode* newMouse = (LLNode*) malloc(sizeof(LLNode));
			newMouse->pData = mouseEvt;
			addNodeToList(&currMouseList, newMouse);
		}
	}
	else if (eventType == SDL_MOUSEBUTTONUP) {
		mouseEvt->type = MOUSE_EVT_BTN_UP;

		LLNode* prevNode = NULL;
		currNode = currMouseList.pHead;

		while (currNode != NULL) {
			currMouse = (MouseEvent*) currNode->pData;

			if (currMouse->btn == mouseEvt->btn) {
				LLNode* newCurrNode = currNode->pNext;

				if (prevNode != NULL) {
					prevNode->pNext = currNode->pNext;
				}
				else {
					currMouseList.pHead = currNode->pNext;
				}

				if (currNode->pNext == NULL) {
					currMouseList.pTail = prevNode;
				}

				free(currMouse);
				free(currNode);

				currNode = newCurrNode;

				currMouseList.size--;
			}
			else {
				prevNode = currNode;
				currNode = currNode->pNext;
			}
		}
	}
}
#endif

void inp_process_event(InputEvent* evt) {
	switch (evt->type) {
        case INPUT_TYPE_KEYB: {
			KeyEvent* keyEvt = (KeyEvent*) evt->event;
            break;
        }
            
        default:
            break;
	}
}

void inp_flush_input_events() {

}
