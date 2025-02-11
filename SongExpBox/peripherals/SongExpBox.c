#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// #include "./constants/GPIO_Constants.h"
// #include "./constants/Musical_Note_Constants.h"
// #include "./types/Adjustment.h"
// #include "./headers/play_note.h"

#define BUZZER_LEFT_1 21  
#define BUZZER_RIGHT_1 10

#define PWM_CLOCK_SOURCE 125000000.0000000000

#define C_0_FREQUENCY 16.35160
#define C_0_WRAP 61992
#define C_0_INTEGER 123
#define C_0_FRACTIONAL 5.0000000000
#define C_0_DIVIDER (PWM_CLOCK_SOURCE/(C_0_FREQUENCY*(C_0_WRAP+1)))

// C 4 
#define C_4_FREQUENCY 261.6256
#define C_4_WRAP 64783
#define C_4_INTEGER 7
#define C_4_FRACTIONAL 6.0000000000
#define C_4_DIVIDER (PWM_CLOCK_SOURCE/(C_4_FREQUENCY*(C_4_WRAP+1)))

#define Cs4_FREQUENCY 
#define Cs4_WRAP 
#define Cs4_INTEGER 
#define Cs4_FRACTIONAL 
#define Cs4_DIVIDER (PWM_CLOCK_SOURCE/(Cs4_FREQUENCY*(Cs4_WRAP+1)))

#define Cb4_FREQUENCY 
#define Cb4_WRAP 
#define Cb4_INTEGER 
#define Cb4_FRACTIONAL 
#define Cb4_DIVIDER (PWM_CLOCK_SOURCE/(Cb4_FREQUENCY*(Cb4_WRAP+1)))

// D 4
#define D_4_FREQUENCY 
#define D_4_WRAP 
#define D_4_INTEGER 
#define D_4_FRACTIONAL 
#define D_4_DIVIDER (PWM_CLOCK_SOURCE/(D_4_FREQUENCY*(D_4_WRAP+1)))

#define Ds4_FREQUENCY 
#define Ds4_WRAP 
#define Ds4_INTEGER 
#define Ds4_FRACTIONAL 
#define Ds4_DIVIDER (PWM_CLOCK_SOURCE/(Ds4_FREQUENCY*(Ds4_WRAP+1)))

#define Db4_FREQUENCY 
#define Db4_WRAP 
#define Db4_INTEGER 
#define Db4_FRACTIONAL 
#define Db4_DIVIDER (PWM_CLOCK_SOURCE/(Db4_FREQUENCY*(Db4_WRAP+1)))

// E 4
#define E_4_FREQUENCY 
#define E_4_WRAP 
#define E_4_INTEGER 
#define E_4_FRACTIONAL 
#define E_4_DIVIDER (PWM_CLOCK_SOURCE/(E_4_FREQUENCY*(E_4_WRAP+1)))

#define Es4_FREQUENCY 
#define Es4_WRAP 
#define Es4_INTEGER 
#define Es4_FRACTIONAL 
#define Es4_DIVIDER (PWM_CLOCK_SOURCE/(Es4_FREQUENCY*(Es4_WRAP+1)))

#define Eb4_FREQUENCY 
#define Eb4_WRAP 
#define Eb4_INTEGER 
#define Eb4_FRACTIONAL 
#define Eb4_DIVIDER (PWM_CLOCK_SOURCE/(Eb4_FREQUENCY*(Eb4_WRAP+1)))

// F 4
#define F_4_FREQUENCY 
#define F_4_WRAP 
#define F_4_INTEGER 
#define F_4_FRACTIONAL 
#define F_4_DIVIDER (PWM_CLOCK_SOURCE/(F_4_FREQUENCY*(F_4_WRAP+1)))

#define Fs4_FREQUENCY 
#define Fs4_WRAP 
#define Fs4_INTEGER 
#define Fs4_FRACTIONAL 
#define Fs4_DIVIDER (PWM_CLOCK_SOURCE/(Fs4_FREQUENCY*(Fs4_WRAP+1)))

#define Fb4_FREQUENCY 
#define Fb4_WRAP 
#define Fb4_INTEGER 
#define Fb4_FRACTIONAL 
#define Fb4_DIVIDER (PWM_CLOCK_SOURCE/(Fb4_FREQUENCY*(Fb4_WRAP+1)))

// G 4
#define G_4_FREQUENCY 
#define G_4_WRAP 
#define G_4_INTEGER 
#define G_4_FRACTIONAL 
#define G_4_DIVIDER (PWM_CLOCK_SOURCE/(G_4_FREQUENCY*(G_4_WRAP+1)))

#define Gs4_FREQUENCY 
#define Gs4_WRAP 
#define Gs4_INTEGER 
#define Gs4_FRACTIONAL 
#define Gs4_DIVIDER (PWM_CLOCK_SOURCE/(Gs4_FREQUENCY*(Gs4_WRAP+1)))

#define Gb4_FREQUENCY 
#define Gb4_WRAP 
#define Gb4_INTEGER 
#define Gb4_FRACTIONAL 
#define Gb4_DIVIDER (PWM_CLOCK_SOURCE/(Gb4_FREQUENCY*(Gb4_WRAP+1)))

// A 4
#define A_4_FREQUENCY 
#define A_4_WRAP 
#define A_4_INTEGER 
#define A_4_FRACTIONAL 
#define A_4_DIVIDER (PWM_CLOCK_SOURCE/(A_4_FREQUENCY*(A_4_WRAP+1)))

#define As4_FREQUENCY 
#define As4_WRAP 
#define As4_INTEGER 
#define As4_FRACTIONAL 
#define As4_DIVIDER (PWM_CLOCK_SOURCE/(As4_FREQUENCY*(As4_WRAP+1)))

#define Ab4_FREQUENCY 
#define Ab4_WRAP 
#define Ab4_INTEGER 
#define Ab4_FRACTIONAL 
#define Ab4_DIVIDER (PWM_CLOCK_SOURCE/(Ab4_FREQUENCY*(Ab4_WRAP+1)))

// B 4
#define B_4_FREQUENCY 
#define B_4_WRAP 
#define B_4_INTEGER 
#define B_4_FRACTIONAL 
#define B_4_DIVIDER (PWM_CLOCK_SOURCE/(B_4_FREQUENCY*(B_4_WRAP+1)))

#define Bs4_FREQUENCY 
#define Bs4_WRAP 
#define Bs4_INTEGER 
#define Bs4_FRACTIONAL 
#define Bs4_DIVIDER (PWM_CLOCK_SOURCE/(Bs4_FREQUENCY*(Bs4_WRAP+1)))

#define Bb4_FREQUENCY 
#define Bb4_WRAP 
#define Bb4_INTEGER 
#define Bb4_FRACTIONAL 
#define Bb4_DIVIDER (PWM_CLOCK_SOURCE/(Bb4_FREQUENCY*(Bb4_WRAP+1)))

uint32_t pwm_clock_hz;

typedef struct {
    uint16_t wrap;
    float divider;
} Adjustment;


Adjustment get_divisor_wrap_from_note(char note[3]){

    static Adjustment adjustment; 

    if(note[2] == '0')
    {

        if(note[0] == 'C'){
                 if(note[1] == '-') {adjustment.wrap = C_0_WRAP; adjustment.divider = C_0_DIVIDER;}
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
                 if(note[1] == '-') {  }
            else if(note[1] == '#') {}
            else {}
        }
        else if(note[0] == 'B'){
            if(note[1] == '-') {}
            else if(note[1] == '#') {}
            else {}
        }

    }    


     if(note[2] == '4')
    {

        if(note[0] == 'C'){
                 if(note[1] == '-') {adjustment.wrap = C_4_WRAP; adjustment.divider = C_4_DIVIDER;}
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
                 if(note[1] == '-') {  }
            else if(note[1] == '#') {}
            else {}
        }
        else if(note[0] == 'B'){
            if(note[1] == '-') {}
            else if(note[1] == '#') {}
            else {}
        }

    }    

    printf("adjustment.divider = %.3f - adjustment.wrap = %d \n", adjustment.divider , adjustment.wrap);
 
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
    
    pwm_set_clkdiv(slice, adjustement.divider);
    pwm_set_wrap(slice,  adjustement.wrap);

    pwm_set_chan_level(slice, channel, duty_cycle*(adjustement.wrap+1));

    pwm_set_enabled(slice, true);
    sleep_ms(time_ms);
    pwm_set_enabled(slice, false);

}


int main() {

    stdio_init_all();
    sleep_ms(10000);
    printf("Programa executando\n");

    pwm_clock_hz = clock_get_hz(clk_sys);
    printf("Frequencia fora while: %u Hz\n", pwm_clock_hz);

    //Initial Configurations
    gpio_set_function(BUZZER_LEFT_1, GPIO_FUNC_PWM);
    gpio_set_function(BUZZER_RIGHT_1, GPIO_FUNC_PWM);

    sleep_ms(4000);

    printf("Antes de playnote \n");

    play_note(BUZZER_RIGHT_1, "C-4", 0.5, 3000);

    // O loop vazio. 
    while (true) {
         printf("A frequência do clock do PWM (clk_sys) é: %u Hz\n", pwm_clock_hz);
         sleep_ms(1000);
    }

    return 0;
   
}
