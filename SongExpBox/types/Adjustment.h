#pragma once

#include "pico/stdlib.h"

typedef struct {
    uint16_t wrap;
    float divisor;
} Adjustment;


typedef struct 
{
    int16_t position_x;
    int16_t position_y;

} cursor_data;