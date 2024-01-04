#ifndef TUI_MSGLINE_H
#define TUI_MSGLINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core/types.h"


#define IME_MSG_LINE_MAX_LENGTH 256


typedef struct TUIMsgLine {
    bool bActive;
    rect rect;
    char text[IME_MSG_LINE_MAX_LENGTH];
} TUIMsgLine;


void tui_init_msg_line(TUIMsgLine* msgLine) {
    msgLine->bActive = false;
    memset(msgLine->text, '\0', IME_MSG_LINE_MAX_LENGTH);
}

void tui_show_msg_line(TUIMsgLine* msgLine, char* text) {
    strcpy(msgLine->text, text);
    msgLine->bActive = true;
}

void tui_hide_msg_line(TUIMsgLine* msgLine) {
    msgLine->bActive = false;
}

void tui_redraw_msg_line(TUIMsgLine* msgLine) {
    if (msgLine->bActive) {
        printf("\e[30;47m");
        printf("\e[0;0H");
        printf("%s", msgLine->text);
        printf("\e[0m");
    }
}

#endif
