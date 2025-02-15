
 #include <stdio.h>
#include "./GPIO_BUTTONS_A_B.h"
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "../../screens/screens.h"


extern int screen;
extern bool check;
extern bool allow_get_state_button_B;
extern cursor_data cursor;

// Função única de callback
void gpio_irq_handler(uint gpio, uint32_t events) {

    //Verificando qual botão solicitou a interrupção e setando as flags

    if (gpio == BUTTON_A) {
        screen=1;
    } else if (gpio == BUTTON_B) {

        if(screen == 1 && cursor.position_y == 23){
            screen = 2;
        }
                        //*allow_get_state_button_B &&*//
        else if(screen == 2 &&    cursor.position_x >= 72 &&  cursor.position_x <= 95){            
            check = true;
        }  
       
    }
}



// Função para configurar GPIOs
void gpio_init_buttons() {

    // Configuração do LED como saída
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, 0); // LED inicia apagado

    // Configuração dos botões como entrada com pull-up interno
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

     // Configuração da interrupção usando um único callback
     gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
     gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

}


