#pragma once

#include "pico/stdlib.h"

typedef struct {
    uint16_t wrap;
    float divisor;
} Adjustment;