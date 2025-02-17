#pragma once

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7

/**
 * Inicializa a máquina PIO para controle da matriz de LEDs.
 */
void npInit(uint pin);

/**
 * Atribui uma cor RGB a um LED.
 */
void npSetLED(const uint index,  uint8_t r,  uint8_t g,  uint8_t b);


/**
 * Limpa o buffer de pixels.
 */
void npClear();

/**
 * Escreve os dados do buffer nos LEDs.
 */
void npWrite();


// Modificado do github: https://github.com/BitDogLab/BitDogLab-C/tree/main/neopixel_pio
// Função para converter a posição do matriz para uma posição do vetor.
int getIndex(int x, int y);