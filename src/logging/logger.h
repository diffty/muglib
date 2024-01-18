#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H


typedef enum ELogSeverity {
    ELogSeverity_DEBUG,
    ELogSeverity_INFO,
    ELogSeverity_WARNING,
    ELogSeverity_ERROR,
    ELogSeverity_CRITICAL
} ELogSeverity;

typedef struct LogRecord {
    unsigned int time;
    ELogSeverity severity;
    char* content;
} LogRecord;


void log_write(char* s);

#endif
