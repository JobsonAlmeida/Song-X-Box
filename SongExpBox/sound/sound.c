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
                if(note[1] == '-') {}
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

    else if(note[2] == '5')
    {
        if(note[0] == 'C'){
                if(note[1] == '-')  { adjustment.wrap = C_5_WRAP; adjustment.divider = C_5_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Cs5_Db5_WRAP; adjustment.divider = Cs5_Db5_DIVIDER; }
            else                    { adjustment.wrap = Cb5_WRAP; adjustment.divider = Cb5_DIVIDER; }
        }
        else if(note[0] == 'D'){
                 if(note[1] == '-') { adjustment.wrap = D_5_WRAP; adjustment.divider = D_5_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Ds5_Eb5_WRAP; adjustment.divider = Ds5_Eb5_DIVIDER; }
            else                    { adjustment.wrap = Cs5_Db5_WRAP; adjustment.divider = Cs5_Db5_DIVIDER; }
        }
        else if(note[0] == 'E') {
            if(note[1] == '-')      { adjustment.wrap = E_5_WRAP; adjustment.divider = E_5_DIVIDER;}
            else if(note[1] == '#') { adjustment.wrap = Es5_WRAP; adjustment.divider = Es5_DIVIDER; }
            else                    { adjustment.wrap = Ds5_Eb5_WRAP; adjustment.divider = Ds5_Eb5_DIVIDER; }
        }
        else if(note[0] == 'F'){
            if(note[1] == '-')      { adjustment.wrap = F_5_WRAP; adjustment.divider = F_5_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Fs5_Gb5_WRAP; adjustment.divider = Fs5_Gb5_DIVIDER; }
            else                    { adjustment.wrap = Fb5_WRAP; adjustment.divider = Fb5_DIVIDER; }
        }
        else if(note[0] == 'G'){
            if(note[1] == '-')      { adjustment.wrap = G_5_WRAP; adjustment.divider = G_5_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Gs5_Ab5_WRAP; adjustment.divider = Gs5_Ab5_DIVIDER; }
            else                    { adjustment.wrap = Fs5_Gb5_WRAP; adjustment.divider = Fs5_Gb5_DIVIDER; }
        }
        else if(note[0] == 'A'){
                if(note[1] == '-') { adjustment.wrap = A_5_WRAP; adjustment.divider = A_5_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = As5_Bb5_WRAP; adjustment.divider = As5_Bb5_DIVIDER; }
            else                    { adjustment.wrap = Gs5_Ab5_WRAP; adjustment.divider = Gs5_Ab5_DIVIDER; }
        }
        else if(note[0] == 'B'){
            if(note[1] == '-')      { adjustment.wrap = B_5_WRAP; adjustment.divider = B_5_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Bs5_WRAP; adjustment.divider = Bs5_DIVIDER; }
            else                    { adjustment.wrap = As5_Bb5_WRAP; adjustment.divider = As5_Bb5_DIVIDER; }
        }

    }    


    else if(note[2] == '4')
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


    else if(note[2] == '3')
    {
        if(note[0] == 'C'){
                if(note[1] == '-') { adjustment.wrap = C_3_WRAP; adjustment.divider = C_3_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Cs3_Db3_WRAP; adjustment.divider = Cs3_Db3_DIVIDER; }
            else                    { adjustment.wrap = Cb3_WRAP; adjustment.divider = Cb3_DIVIDER; }
        }
        else if(note[0] == 'D'){
            if(note[1] == '-')      { adjustment.wrap = D_3_WRAP; adjustment.divider = D_3_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Ds3_Eb3_WRAP; adjustment.divider = Ds3_Eb3_DIVIDER; }
            else                    { adjustment.wrap = Cs3_Db3_WRAP; adjustment.divider = Cs3_Db3_DIVIDER; }
        }
        else if(note[0] == 'E') {
            if(note[1] == '-')      { adjustment.wrap = E_3_WRAP; adjustment.divider = E_3_DIVIDER;}
            else if(note[1] == '#') { adjustment.wrap = Es3_WRAP; adjustment.divider = Es3_DIVIDER; }
            else                    { adjustment.wrap = Ds3_Eb3_WRAP; adjustment.divider = Ds3_Eb3_DIVIDER; }
        }
        else if(note[0] == 'F'){
            if(note[1] == '-')      { adjustment.wrap = F_3_WRAP; adjustment.divider = F_3_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Fs3_Gb3_WRAP; adjustment.divider = Fs3_Gb3_DIVIDER; }
            else                    { adjustment.wrap = Fb3_WRAP; adjustment.divider = Fb3_DIVIDER; }
        }
        else if(note[0] == 'G'){
            if(note[1] == '-')      { adjustment.wrap = G_3_WRAP; adjustment.divider = G_3_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Gs3_Ab3_WRAP; adjustment.divider = Gs3_Ab3_DIVIDER; }
            else                    { adjustment.wrap = Fs3_Gb3_WRAP; adjustment.divider = Fs3_Gb3_DIVIDER; }
        }
        else if(note[0] == 'A'){
                if(note[1] == '-') { adjustment.wrap = A_3_WRAP; adjustment.divider = A_3_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = As3_Bb3_WRAP; adjustment.divider = As3_Bb3_DIVIDER; }
            else                    { adjustment.wrap = Gs3_Ab3_WRAP; adjustment.divider = Gs3_Ab3_DIVIDER; }
        }
        else if(note[0] == 'B'){
            if(note[1] == '-')      { adjustment.wrap = B_3_WRAP; adjustment.divider = B_3_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Bs3_WRAP; adjustment.divider = Bs3_DIVIDER; }
            else                    { adjustment.wrap = As3_Bb3_WRAP; adjustment.divider = As3_Bb3_DIVIDER; }
        }

    } 

    //printf("adjustment.divider = %.3f - adjustment.wrap = %d \n", adjustment.divider , adjustment.wrap);

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
