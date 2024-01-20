#ifndef LOGGING_STDOUT_ADAPTER_H
#define LOGGING_STDOUT_ADAPTER_H

#include <stdio.h>
#include <stdlib.h>

#include "base.h"


void logger_stdout_init() {

}

void logger_stdout_print(char* s) {
    printf("%s\n", s);
}

LogAdapter create_stdout_logger_adapter() {
    LogAdapter stdoutAdapter;
    stdoutAdapter.initFunc = &logger_stdout_init;
    stdoutAdapter.printFunc = &logger_stdout_print;
    return stdoutAdapter;
}

#endif
