#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "./constants/GPIO_Constants.h"
#include "./constants/Musical_Note_Constants.h"
#include "./types/Adjustment.h"
// #include "./headers/play_note.h"

uint32_t pwm_clock_hz;

Adjustment get_divisor_wrap_from_note(char note[3]){

    static Adjustment adjustment; 

    if(note[2] == '0'){

        if(note[0] == 'C'){
                 if(note[1] == '-') {    }
            else if(note[1] == '#') {}
            else                    {  }
        }

        else if(note[0] == 'D'){
            if(note[1] == '-') {}
            else if(note[1] == '#') {}
            else {}
        }
        else if(note[0] == 'E'){
            if(note[1] == '-') {}
            else if(note[1] == '#') {}
            else {}
        }
        else if(note[0] == 'F'){
            if(note[1] == '-') {}
            else if(note[1] == '#') {}
            else {}
        }
        else if(note[0] == 'G'){
            if(note[1] == '-') {}
            else if(note[1] == '#') {}
            else {}
        }
        else if(note[0] == 'A'){
                 if(note[1] == '-') { adjustment.wrap = A0_WRAP; adjustment.divisor = pwm_clock_hz/(A0_FREQUENCY * (adjustment.wrap+1)); printf("encontrou nota A-0\n"); }
            else if(note[1] == '#') {}
            else {}
        }
        else if(note[0] == 'B'){
            if(note[1] == '-') {}
            else if(note[1] == '#') {}
            else {}
        }

    }    

    printf("adjustment.divisor = %.3f - adjustment.wrap = %d \n", adjustment.divisor , adjustment.wrap);
 
    return adjustment;

}


void play_note(uint buzzer_id, char note[3], float duty_cycle, float time_ms){

    printf("Dentro de playnote\n");

    // static varibale so the they are not created every time
    static uint slice = 2;
    static uint channel = 1;
    static Adjustment adjustement = {0, 0.0f};

    slice = pwm_gpio_to_slice_num(buzzer_id);
    channel = pwm_gpio_to_channel(buzzer_id);    

    adjustement = get_divisor_wrap_from_note(note);
    pwm_set_clkdiv(slice, adjustement.divisor);
    pwm_set_wrap(slice,  adjustement.wrap);

    pwm_set_chan_level(slice, channel, duty_cycle*(adjustement.wrap+1));

    pwm_set_enabled(slice, true);
    sleep_ms(time_ms);
    pwm_set_enabled(slice, false);

}



int main() {

    stdio_init_all();
    sleep_ms(15000);
    printf("Programa executando\n");

    pwm_clock_hz = clock_get_hz(clk_sys);
    printf("Frequencia fora while: %u Hz\n", pwm_clock_hz);

    //Initial Configurations
    gpio_set_function(BUZZER_LEFT_1, GPIO_FUNC_PWM);
    gpio_set_function(BUZZER_RIGHT_1, GPIO_FUNC_PWM);

    sleep_ms(4000);

    printf("Antes de playnote \n");

    play_note(BUZZER_RIGHT_1, "A-0", 0.5, 3000);

    // O loop vazio. 
    while (true) {
         printf("A frequência do clock do PWM (clk_sys) é: %u Hz\n", pwm_clock_hz);
         sleep_ms(1000);
    }

    return 0;
   
}
