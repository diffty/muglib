#include "../core/system.h"
#include "logger.h"


void log_write(char* s) {
    System* mainSys = sys_get_system_instance();
    sys_log_to_all_adapters(mainSys, s);
}
