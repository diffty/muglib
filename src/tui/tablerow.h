#ifndef TUI_TABLEROW_H
#define TUI_TABLEROW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core/types.h"


#define IME_LINE_EDIT_MAX_LENGTH 256


typedef struct TUITableRow {
    int nbColumns;
    char** columnsData;
    int* aCellStyle;
} TUITableRow;


void tui_init_table_row(TUITableRow* tuiTableRow, int nbColumns) {
    tuiTableRow->aCellStyle = NULL;
    tuiTableRow->nbColumns = nbColumns;
    tuiTableRow->columnsData = (char**) malloc(1 * nbColumns * sizeof(char*));
    int i;
    for (i = 0; i < nbColumns; i++) {
        tuiTableRow->columnsData[i] = (char*) malloc(1 * sizeof(char));
        tuiTableRow->columnsData[i][0] = '\0';
    }
}

void tui_free_table_row(TUITableRow* tuiTableRow) {
    // TODO: #FreeColumsData
    free(tuiTableRow->aCellStyle);
    free(tuiTableRow->columnsData);
}

void tui_redraw_table_row(TUITableRow* tuiTableRow) {

}

#endif