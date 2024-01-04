#ifndef TUI_LINEEDIT_H
#define TUI_LINEEDIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core/types.h"
#include "../utils/time.h"


#define IME_LINE_EDIT_MAX_LENGTH 256


typedef struct TUILineEdit {
    bool bActive;
    rect rect;
    char text[IME_LINE_EDIT_MAX_LENGTH];
    char title[IME_LINE_EDIT_MAX_LENGTH];
} TUILineEdit;


void tui_init_line_edit(TUILineEdit* lineEdit) {
    lineEdit->bActive = false;
    memset(lineEdit->title, '\0', IME_LINE_EDIT_MAX_LENGTH);
    memset(lineEdit->text, '\0', IME_LINE_EDIT_MAX_LENGTH);
}

void tui_show_line_edit(TUILineEdit* lineEdit, char* title, char* initText) {
    strcpy(lineEdit->title, title);
    if (initText != NULL) strcpy(lineEdit->text, initText);
    lineEdit->bActive = true;
}

void tui_hide_line_edit(TUILineEdit* lineEdit) {
    lineEdit->bActive = false;
}

void tui_redraw_line_edit(TUILineEdit* lineEdit) {
    if (lineEdit->bActive) {
        char caretCharacter = '_';
        if (((int) get_current_time()) % 2 == 1) { // TODO: make a timestamp helper returning only seconds
            caretCharacter = ' ';
        }

        printf("\e[30;47m");
        printf("\e[0;0H");
        printf("%s: %s%c", lineEdit->title, lineEdit->text, caretCharacter);
        printf("\e[0m");
    }
}

#endif
