#ifndef LOGGING_BASE_ADAPTER_H
#define LOGGING_BASE_ADAPTER_H

typedef struct LogAdapter {
    void (*initFunc);
    void (*printFunc)(char*);
} LogAdapter;

#endif
