#include "ADC_types.h"

// Configura o adc
void setup_adc();

//Configura o DMA para utilizar os dados do ADC
void setup_dma_adc();

//Invoca as funções setup_adc e setup_dma_adc para configurar
// o adc e o dma 
void setup_adc_and_dma();

// Retorna a velocidade e a direção informada pelo joysctick do movimento que será 
// realizado pelo cursor no display
joystick_data velocity_and_direction(uint16_t buffer_adc_x[]);