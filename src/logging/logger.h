#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

#include <time.h>
#include "adapters/base.h"
#include "../utils/list.h"


typedef enum ELogSeverity {
    ELogSeverity_DEBUG,
    ELogSeverity_INFO,
    ELogSeverity_WARNING,
    ELogSeverity_ERROR,
    ELogSeverity_CRITICAL
} ELogSeverity;

typedef struct LogRecord {
    time_t time;
    ELogSeverity severity;
    char* message;
} LogRecord;

typedef struct LogFormatter {
    char* (*formatterFunc)(LogRecord* s);
} LogFormatter;

typedef struct Logger {
    List logAdapterList;
    LogFormatter* logFormatter;
} Logger;


void log_write(Logger* pLogger, char* s);
void log_logger_set_formatter(Logger* pLogger, LogFormatter* logFormatter);
void log_logger_add_adapter(Logger* pLogger, LogAdapter logAdapter);
void log_logger_write_logrecord(Logger* pLogger, LogRecord* logRecord);

#endif
