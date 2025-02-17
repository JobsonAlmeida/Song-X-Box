
#include <stdio.h>
#include "./GPIO_BUTTONS_A_B.h"
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "../../screens/screens.h"

#define TIME_FOR_NEXT_PRESSURE 2000


extern int screen;
extern bool check;
extern bool allow_get_state_button_B;
extern int level;
extern int initial_page;

extern cursor_data cursor;

extern bool play_secret_note;


bool allow_action_edge_fall_button_B = true;
bool allow_acion_edge_rise_button_B = true;



int64_t allow_pressure(alarm_id_t id, void *user_data) {

    printf("entrou callback\n");
    allow_action_edge_fall_button_B = true;
    allow_acion_edge_rise_button_B = true;
    
    return 0;
}


// Função única de callback
void gpio_irq_handler(uint gpio, uint32_t events) {

    //Verificando qual botão solicitou a interrupção e setando as flags

    if (gpio == BUTTON_A) {
        screen=1;
    } else if (gpio == BUTTON_B) {

        //Borda de descida detectada -> Botão pressionado
        if ( (events & GPIO_IRQ_EDGE_FALL) && allow_action_edge_fall_button_B ) {
           
            if(screen == 1 && cursor.position_y == 23){
                screen = 2;
            }
            else if(screen == 2 && cursor.position_x >= 72 &&  cursor.position_x <= 95){            
                check = true;
            } 
            else if(screen == 2 && cursor.position_x >= 32 && cursor.position_x <=39) {
                play_secret_note = true;
            }

            allow_action_edge_fall_button_B = false;

        }
        if ( (events & GPIO_IRQ_EDGE_RISE) && allow_acion_edge_rise_button_B) {

            allow_acion_edge_rise_button_B = false;            
            add_alarm_in_ms(TIME_FOR_NEXT_PRESSURE, allow_pressure, NULL, true);
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
     gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_RISE, true, &gpio_irq_handler);


}


