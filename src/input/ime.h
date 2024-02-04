#ifndef INPUT_IME
#define INPUT_IME

#include <psp2/libime.h>


typedef struct ImeSystem {
    uint16_t* inputBuffer;
    int bVisible;
    int maxLength;

    #ifdef TARGET_PSVITA
        SceImeParam imeParam;
        SceUInt32 imeWork[SCE_IME_WORK_BUFFER_SIZE / sizeof(SceInt32)];
    #endif
} ImeSystem;


void ime_event_handler(void *arg, const SceImeEventData *e) {
    switch (e->id) {
        case SCE_IME_EVENT_UPDATE_TEXT:
        {  
            break;
        }

        case SCE_IME_EVENT_PRESS_CLOSE:
        {
            *((int*) arg) = 0;
            sceImeClose();
            break;
        }
    }
}

void ime_init_ime_system(ImeSystem* imeSys, int maxLength) {
    imeSys->bVisible = 0;
    imeSys->maxLength = maxLength;
    imeSys->inputBuffer = malloc(imeSys->maxLength * sizeof(uint16_t));
    memset(imeSys->inputBuffer, '\0', imeSys->maxLength * sizeof(uint16_t));

    #ifdef TARGET_PSVITA
        sceSysmoduleLoadModule(SCE_SYSMODULE_IME); 
        sceImeParamInit(&imeSys->imeParam);
    #endif
}

void ime_free_ime_system(ImeSystem* imeSys) {
    free(imeSys->inputBuffer);
}

void ime_toggle_ime_system(ImeSystem* imeSys, SceWChar16* initialText) {
    if (!imeSys->bVisible) {
        imeSys->bVisible = true;

        imeSys->imeParam.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH;
        imeSys->imeParam.languagesForced = SCE_TRUE;
        imeSys->imeParam.type = SCE_IME_TYPE_DEFAULT;
        imeSys->imeParam.option = 0;
        imeSys->imeParam.inputTextBuffer = imeSys->inputBuffer;
        imeSys->imeParam.handler = ime_event_handler;

        if (initialText == NULL) {
            imeSys->imeParam.initialText = "";
        }
        else {
            imeSys->imeParam.initialText = initialText;
        }

        imeSys->imeParam.maxTextLength = (SceUInt32) imeSys->maxLength;
        imeSys->imeParam.enterLabel = SCE_IME_ENTER_LABEL_DEFAULT;
        imeSys->imeParam.work = imeSys->imeWork;
        imeSys->imeParam.arg = &imeSys->bVisible;

        SceInt32 res = sceImeOpen(&imeSys->imeParam);
        if (res > 0) {
            printf("There was a problem opening IME keyboard (%d)", res);
        }
    }
    else {
        imeSys->bVisible = false;
        sceImeClose();
    }
}

void ime_update(ImeSystem* imeSys) {
    #ifdef TARGET_PSVITA
        sceImeUpdate();
    #endif
}

#endif