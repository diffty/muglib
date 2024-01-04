#ifndef TUI_LABEL_H
#define TUI_LABEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core/types.h"


typedef struct TUILabel {
    rect rect;
    char* title;
    char* text;
    char* textSrcPtr;
} TUILabel;


void tui_init_label(TUILabel* tuiLabel, char* text, char* title) {
    tuiLabel->text = (char*) malloc(strlen(text) + 1);
    strcpy(tuiLabel->text, text);

    if (title == NULL) {
        tuiLabel->title = (char*) malloc(1);
        tuiLabel->title[0] = '\0';
    }
    else {
        tuiLabel->title = (char*) malloc(strlen(title) + 1);
        strcpy(tuiLabel->title, title);
    }
}

void tui_free_label(TUILabel* tuiLabel) {
    free(tuiLabel->text);
    free(tuiLabel->title);
}

void tui_draw_label(TUILabel* tuiLabel) {
    printf("\e[%ld;%ldH", tuiLabel->rect.y, tuiLabel->rect.x);
    char* textToDraw;

    textToDraw = tuiLabel->text;

    if (tuiLabel->title == '\0') {
        printf("%s", textToDraw);
    }
    else {
        printf("%s: %s", tuiLabel->title, textToDraw);
    }
}

#endif
