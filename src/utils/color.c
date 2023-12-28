#include "color.h"


color4 create_rgba(uint8 r, uint8 g, uint8 b, uint8 a) {
    color4 c = { r, b, g, 255 };
    return c;
}