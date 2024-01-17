#include "random.h"
#include "../core/system.h"
#include "../utils/time.h"


int get_rand_int(int iMin, int iMax) {
    System* pSystem = sys_get_system_instance();
    srand((unsigned int) ((get_current_time() - (long) get_current_time()) * 1000000000));
    return iMin + rand() % (iMax - iMin);
}

float get_rand_float(float fMin, float fMax) {
    srand((unsigned int) ((get_current_time() - (long) get_current_time()) * 1000000000));
    return fMin + (((float) rand()) / RAND_MAX) * (fMax - fMin);
}
