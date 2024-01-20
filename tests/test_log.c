#ifndef TEST_LOG
#define TEST_LOG

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/core/types.h"
#include "../src/core/system.h"
#include "../src/logging/logger.h"
#include "../src/logging/adapters/stdout.h"
#include "../src/utils/strings.h"


char* defaultLogFormatterFunc(LogRecord* pLogRecord) {
    String formattedStr = String("");

    struct tm* pLocalTime = localtime(&pLogRecord->time);

    char dateTimeStr[20];
    strftime(dateTimeStr, 20, "%d/%m/%Y %H:%M:%S", pLocalTime);

    str_concat(&formattedStr, dateTimeStr);
    str_concat(&formattedStr, " | ");
    str_concat(&formattedStr, pLogRecord->message);

    return formattedStr.data;
}

char* otherLogFormatterFunc(LogRecord* pLogRecord) {
    String formattedStr = String("");

    struct tm* pLocalTime = localtime(&pLogRecord->time);

    char dateTimeStr[20];
    strftime(dateTimeStr, 20, "[%d/%m/%Y %H:%M:%S]", pLocalTime);

    str_concat(&formattedStr, dateTimeStr);
    str_concat(&formattedStr, " ");
    str_concat(&formattedStr, pLogRecord->message);

    return formattedStr.data;
}

int main() {
    System mainSys;
    sys_init_system(&mainSys);

    Logger mainLogger;
    mainLogger.logAdapterList = List(LogAdapter);
    LogFormatter logFormatter;
    logFormatter.formatterFunc = &defaultLogFormatterFunc;
    log_logger_set_formatter(&mainLogger, &logFormatter);

    Logger altLogger;
    altLogger.logAdapterList = List(LogAdapter);
    LogFormatter logFormatter2;
    logFormatter2.formatterFunc = &otherLogFormatterFunc;
    log_logger_set_formatter(&altLogger, &logFormatter2);

    LogAdapter stdoutLogAdapter = create_stdout_logger_adapter();
    LogAdapter stdoutLogAdapter2 = create_stdout_logger_adapter();

    sys_add_logger(&mainSys, &mainLogger);
    sys_add_logger(&mainSys, &altLogger);

    log_logger_add_adapter(&mainLogger, stdoutLogAdapter);
    log_logger_add_adapter(&mainLogger, stdoutLogAdapter2);
    log_logger_add_adapter(&altLogger, stdoutLogAdapter2);

    sys_log_to_all_adapters(&mainSys, "test");
    return 0;
}

#endif
