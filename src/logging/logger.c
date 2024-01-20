#include "../core/system.h"
#include "logger.h"


void log_write(Logger* pLogger, char* s) {
    System* mainSys = sys_get_system_instance();
    sys_log_to_all_adapters(mainSys, s);
}

void log_logger_set_formatter(Logger* pLogger, LogFormatter* logFormatter) {
    pLogger->logFormatter = logFormatter;
}

void log_logger_add_adapter(Logger* pLogger, LogAdapter logAdapter) {
    lst_append(&pLogger->logAdapterList, &logAdapter);
}

void log_logger_write_logrecord(Logger* pLogger, LogRecord* logRecord) {
    int i;
    for (i = 0; i < pLogger->logAdapterList.count; i++) {
        LogAdapter currLogAdapter = *((LogAdapter*) lst_get(&pLogger->logAdapterList, i));
        char* formattedMsg = pLogger->logFormatter->formatterFunc(logRecord);
        currLogAdapter.printFunc(formattedMsg);
        free(formattedMsg);
    }
}