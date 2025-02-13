#pragma once

#include "../peripherals/I2C_Display/ssd1306.h"

typedef struct 
{
    int16_t position_x;
    int16_t position_y;

} cursor_data;



// Define a tela 
void screen0();

// Define a tela 1
void screen1();

// Define a tela 2
void screen2();