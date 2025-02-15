#include <stdio.h>
#include "hardware/pwm.h"
#include "sound.h"
#include "note_parameters.h"

uint32_t pwm_clock_hz;

// Struct para ser passada para a função de callback repeating_timer_callback
struct Data_Struct{
    uint slice;
};
struct Data_Struct data_note;


void buzzers_config(){
    //Initial Configurations
    gpio_set_function(BUZZER_LEFT_1, GPIO_FUNC_PWM);
    gpio_set_function(BUZZER_RIGHT_1, GPIO_FUNC_PWM);
    return;
}


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
                if(note[1] == '-') { adjustment.wrap = C_4_WRAP; adjustment.divider = C_4_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Cs4_Db4_WRAP; adjustment.divider = Cs4_Db4_DIVIDER; }
            else                    { adjustment.wrap = Cb4_WRAP; adjustment.divider = Cb4_DIVIDER; }
        }
        else if(note[0] == 'D'){
            if(note[1] == '-')      { adjustment.wrap = D_4_WRAP; adjustment.divider = D_4_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Ds4_Eb4_WRAP; adjustment.divider = Ds4_Eb4_DIVIDER; }
            else                    { adjustment.wrap = Cs4_Db4_WRAP; adjustment.divider = Cs4_Db4_DIVIDER; }
        }
        else if(note[0] == 'E') {
            if(note[1] == '-')      { adjustment.wrap = E_4_WRAP; adjustment.divider = E_4_DIVIDER;}
            else if(note[1] == '#') { adjustment.wrap = Es4_WRAP; adjustment.divider = Es4_DIVIDER; }
            else                    { adjustment.wrap = Ds4_Eb4_WRAP; adjustment.divider = Ds4_Eb4_DIVIDER; }
        }
        else if(note[0] == 'F'){
            if(note[1] == '-')      { adjustment.wrap = F_4_WRAP; adjustment.divider = F_4_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Fs4_Gb4_WRAP; adjustment.divider = Fs4_Gb4_DIVIDER; }
            else                    { adjustment.wrap = Fb4_WRAP; adjustment.divider = Fb4_DIVIDER; }
        }
        else if(note[0] == 'G'){
            if(note[1] == '-')      { adjustment.wrap = G_4_WRAP; adjustment.divider = G_4_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Gs4_Ab4_WRAP; adjustment.divider = Gs4_Ab4_DIVIDER; }
            else                    { adjustment.wrap = Fs4_Gb4_WRAP; adjustment.divider = Fs4_Gb4_DIVIDER; }
        }
        else if(note[0] == 'A'){
                if(note[1] == '-') { adjustment.wrap = A_4_WRAP; adjustment.divider = A_4_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = As4_Bb4_WRAP; adjustment.divider = As4_Bb4_DIVIDER; }
            else                    { adjustment.wrap = Gs4_Ab4_WRAP; adjustment.divider = Gs4_Ab4_DIVIDER; }
        }
        else if(note[0] == 'B'){
            if(note[1] == '-')      { adjustment.wrap = B_4_WRAP; adjustment.divider = B_4_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Bs4_WRAP; adjustment.divider = Bs4_DIVIDER; }
            else                    { adjustment.wrap = As4_Bb4_WRAP; adjustment.divider = As4_Bb4_DIVIDER; }
        }

    }    

    printf("adjustment.divider = %.3f - adjustment.wrap = %d \n", adjustment.divider , adjustment.wrap);

    return adjustment;

}


int64_t stop_note(alarm_id_t id, void *user_data) {

    struct Data_Struct* data = (struct Data_Struct*) user_data;

    pwm_set_enabled(data->slice, false);

    return 0;

}


void play_note(uint buzzer_id, char note[3], float duty_cycle, uint32_t time_ms){

    // static varibale so that they are not created every time
    // just initializing because they are static 
    static uint slice = 2; 
    static uint channel = 1;
    static Adjustment adjustement = {0, 0.0f};

    slice = pwm_gpio_to_slice_num(buzzer_id);
    channel = pwm_gpio_to_channel(buzzer_id);    

    adjustement = get_divisor_wrap_from_note(note);
    
    pwm_set_clkdiv(slice, adjustement.divider);
    pwm_set_wrap(slice,  adjustement.wrap);

    pwm_set_chan_level(slice, channel, duty_cycle*(adjustement.wrap+1));

    data_note.slice = slice;

    pwm_set_enabled(slice, true);

    add_alarm_in_ms(time_ms, stop_note, &data_note, false);

    return;
}
