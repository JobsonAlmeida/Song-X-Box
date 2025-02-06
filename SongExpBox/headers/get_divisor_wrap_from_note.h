#pragma once

#include "pico/stdlib.h"
#include "../types/Adjustment.h"

extern uint32_t pwm_clock_hz;

Adjustment get_divisor_wrap_from_note(char note[3]);