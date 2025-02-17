 // ----------- ADC e DMA -------------

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#include "peripherals/ADC_DMA/ADC_DMA_functions.h"
#include "screens/screens.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "peripherals/I2C_Display/ssd1306.h"
#include "hardware/i2c.h"
#include "peripherals/GPIO_BUTTONS_A_B/GPIO_BUTTONS_A_B.h"
#include "sound/sound.h"

#include "peripherals/MATRIZ_RGB/matriz_rgb.h"
 

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

extern uint16_t x_axis_buffer[];
extern uint16_t y_axis_buffer[];

extern int dma_chan_0;
extern int dma_chan_1;

int screen;

cursor_data cursor;

int main() {
 
     // ---- REFERENTE À INICIALIZAÇÃO DO DISPLAY ---- 
 
     // Inicialização do i2c
     i2c_init(i2c1, ssd1306_i2c_clock * 1000);
     gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
     gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
     gpio_pull_up(I2C_SDA);
     gpio_pull_up(I2C_SCL);
 
     // Processo de inicialização completo do OLED SSD1306
     ssd1306_init();
 
    
 
     // ---------- REFERENTE À INICIALIZAÇÃO DO ADC -------------
     stdio_init_all();
     setup_adc_and_dma(); // Inicia o adc e o dma correpondente ao adc  

     /// gpio BUTTONS A E B
     gpio_init_buttons();

     // Buzzers
     buzzers_config();


     //Matriz RGB

      // Inicializa entradas e saídas.
     stdio_init_all();

     // Inicializa matriz de LEDs NeoPixel.
     npInit(LED_PIN);
     npClear();

     screen = 0; 
     while (true) {
 
             if (screen == 0) screen0();
        else if (screen == 1) screen1();
        else if (screen == 2) screen2();           
     };
         
     return 0;
  
}
 

// int main() {

// irq_set_enabled(PWM_IRQ_WRAP, true);  // Habilitar as interrupções de PWM (se necessário)

// stdio_init_all();

// uint32_t pwm_clock_hz = clock_get_hz(clk_sys);
// printf("Frequencia fora while: %u Hz\n", pwm_clock_hz);

// //Initial Configurations
// gpio_set_function(BUZZER_LEFT_1, GPIO_FUNC_PWM);
// gpio_set_function(BUZZER_RIGHT_1, GPIO_FUNC_PWM);

// // sleep_ms(4000);

// printf("Antes de playnote \n");

// play_note(BUZZER_RIGHT_1, "A-4", 0.005, 2000);

// // O loop vazio. 
// while (true) {
//      //  printf("A frequência do clock do PWM (clk_sys) é: %u Hz\n", pwm_clock_hz);
//      //  sleep_ms(1000);

//      tight_loop_contents(); // Função que otimiza o loop vazio para evitar consumo excessivo de CPU.
// }

// return 0;

// }











// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "hardware/pio.h"
// #include "hardware/clocks.h"

// // Biblioteca gerada pelo arquivo .pio durante compilação.
// #include "ws2818b.pio.h"

// // Definição do número de LEDs e pino.
// #define LED_COUNT 25
// #define LED_PIN 7

// // Definição de pixel GRB
// struct pixel_t {
//   uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
// };
// typedef struct pixel_t pixel_t;
// typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

// // Declaração do buffer de pixels que formam a matriz.
// npLED_t leds[LED_COUNT];

// // Variáveis para uso da máquina PIO.
// PIO np_pio;
// uint sm;

// /**
//  * Inicializa a máquina PIO para controle da matriz de LEDs.
//  */
// void npInit(uint pin) {

//   // Cria programa PIO.
//   uint offset = pio_add_program(pio0, &ws2818b_program);
//   np_pio = pio0;

//   // Toma posse de uma máquina PIO.
//   sm = pio_claim_unused_sm(np_pio, false);
//   if (sm < 0) {
//     np_pio = pio1;
//     sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
//   }

//   // Inicia programa na máquina PIO obtida.
//   ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

//   // Limpa buffer de pixels.
//   for (uint i = 0; i < LED_COUNT; ++i) {
//     leds[i].R = 0;
//     leds[i].G = 0;
//     leds[i].B = 0;
//   }
// }

// /**
//  * Atribui uma cor RGB a um LED.
//  */
// void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
//   leds[index].R = r;
//   leds[index].G = g;
//   leds[index].B = b;
// }

// /**
//  * Limpa o buffer de pixels.
//  */
// void npClear() {
//   for (uint i = 0; i < LED_COUNT; ++i)
//     npSetLED(i, 0, 0, 0);
// }

// /**
//  * Escreve os dados do buffer nos LEDs.
//  */
// void npWrite() {
//   // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
//   for (uint i = 0; i < LED_COUNT; ++i) {
//     pio_sm_put_blocking(np_pio, sm, leds[i].G);
//     pio_sm_put_blocking(np_pio, sm, leds[i].R);
//     pio_sm_put_blocking(np_pio, sm, leds[i].B);
//   }
//   sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
// }


// // Modificado do github: https://github.com/BitDogLab/BitDogLab-C/tree/main/neopixel_pio
// // Função para converter a posição do matriz para uma posição do vetor.
// int getIndex(int x, int y) {
//   // Se a linha for par (0, 2, 4), percorremos da esquerda para a direita.
//   // Se a linha for ímpar (1, 3), percorremos da direita para a esquerda.
//   if (y % 2 == 0) {
//       return 24-(y * 5 + x); // Linha par (esquerda para direita).
//   } else {
//       return 24-(y * 5 + (4 - x)); // Linha ímpar (direita para esquerda).
//   }
// }


// int main() {

//   // Inicializa entradas e saídas.
//   stdio_init_all();

//   // Inicializa matriz de LEDs NeoPixel.
//   npInit(LED_PIN);
//   npClear();

//   // Aqui, você desenha nos LEDs.

//   npWrite(); // Escreve os dados nos LEDs.

//   // Não faz mais nada. Loop infinito.
//   while (true) {

//     int matriz1[5][5][3] = {
//       {{29, 16, 242}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {29, 16, 242}},
//       {{0, 0, 0}, {29, 16, 242}, {0, 0, 0}, {29, 16, 242}, {0, 0, 0}},
//       {{0, 0, 0}, {0, 0, 0}, {29, 16, 242}, {0, 0, 0}, {0, 0, 0}},
//       {{0, 0, 0}, {29, 16, 242}, {0, 0, 0}, {29, 16, 242}, {0, 0, 0}},
//       {{29, 16, 242}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {29, 16, 242}}
//     };

//     // Desenhando Sprite contido na matriz.c
//     for(int linha = 0; linha < 5; linha++){
//       for(int coluna = 0; coluna < 5; coluna++){
//         int posicao = getIndex(linha, coluna);
//         npSetLED(posicao, matriz1[coluna][linha][0], matriz1[coluna][linha][1], matriz1[coluna][linha][2]);
//       }
//     }

//     npWrite();
//     sleep_ms(2000);
//     npClear();

//     int matriz2[5][5][3] = 
//     {
//       {{16, 242, 82}, {16, 242, 82}, {16, 242, 82}, {195, 21, 206}, {195, 21, 206}},
//       {{16, 242, 82}, {16, 242, 82}, {16, 242, 82}, {242, 16, 66}, {242, 16, 66}},
//       {{242, 16, 66}, {242, 16, 66}, {16, 242, 82}, {242, 16, 66}, {242, 16, 66}},
//       {{242, 16, 66}, {242, 16, 66}, {16, 242, 82}, {16, 242, 82}, {16, 242, 82}},
//       {{195, 21, 206}, {195, 21, 206}, {16, 242, 82}, {16, 242, 82}, {16, 242, 82}}
//     };


//     // Desenhando Sprite contido na matriz.c
//     for(int linha = 0; linha < 5; linha++){
//       for(int coluna = 0; coluna < 5; coluna++){
//         int posicao = getIndex(linha, coluna);
//         npSetLED(posicao, matriz2[coluna][linha][0], matriz2[coluna][linha][1], matriz2[coluna][linha][2]);
//       }
//     }

//     npWrite();
//     sleep_ms(2000);

//     }

// }
