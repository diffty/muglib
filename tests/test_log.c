#ifndef TEST_LOG
#define TEST_LOG

#include <stdio.h>
#include <stdlib.h>

#include "../src/core/system.h"
#include "../src/logging/logger.h"
#include "../src/logging/adapters/stdout.h"


int main() {
    System mainSys;
    sys_init_system(&mainSys);

    LogAdapter stdoutLogAdapter = create_stdout_logger();
    sys_add_logger_adapter(&mainSys, &stdoutLogAdapter);
    sys_log_to_all_adapters(&mainSys, "test");
}

#endif
