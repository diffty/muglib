#include "../src/utils/strings.h"


int main() {
    String testStr = str_create_string(0, 4);
    printf("%s\n", testStr.data);
    return 0;
}
