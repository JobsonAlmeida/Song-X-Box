#pragma once

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define BUTTON_A 5 
#define BUTTON_B 6 
#define LED_VERMELHO 13

void gpio_init_buttons();

// Funções de interrupção do BUTTON A
void botao_a_isr(uint gpio, uint32_t events);

// Funções de interrupção do BUTTON B
void botao_b_isr(uint gpio, uint32_t events);


