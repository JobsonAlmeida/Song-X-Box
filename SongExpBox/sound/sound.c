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

    if(note[2] == '9')
    {
        if(note[0] == 'C'){
                if(note[1] == '-')  { adjustment.wrap = C_9_WRAP; adjustment.divider = C_9_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Cs9_Db9_WRAP; adjustment.divider = Cs9_Db9_DIVIDER; }
            else                    { adjustment.wrap = Cb9_WRAP; adjustment.divider = Cb9_DIVIDER; }
        }
        else if(note[0] == 'D'){
                 if(note[1] == '-') { adjustment.wrap = D_9_WRAP; adjustment.divider = D_9_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Ds9_Eb9_WRAP; adjustment.divider = Ds9_Eb9_DIVIDER; }
            else                    { adjustment.wrap = Cs9_Db9_WRAP; adjustment.divider = Cs9_Db9_DIVIDER; }
        }
        else if(note[0] == 'E') {
            if(note[1] == '-')      { adjustment.wrap = E_9_WRAP; adjustment.divider = E_9_DIVIDER;}
            else if(note[1] == '#') { adjustment.wrap = Es9_WRAP; adjustment.divider = Es9_DIVIDER; }
            else                    { adjustment.wrap = Ds9_Eb9_WRAP; adjustment.divider = Ds9_Eb9_DIVIDER; }
        }
        else if(note[0] == 'F'){
            if(note[1] == '-')      { adjustment.wrap = F_9_WRAP; adjustment.divider = F_9_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Fs9_Gb9_WRAP; adjustment.divider = Fs9_Gb9_DIVIDER; }
            else                    { adjustment.wrap = Fb9_WRAP; adjustment.divider = Fb9_DIVIDER; }
        }
        else if(note[0] == 'G'){
            if(note[1] == '-')      { adjustment.wrap = G_9_WRAP; adjustment.divider = G_9_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Gs9_Ab9_WRAP; adjustment.divider = Gs9_Ab9_DIVIDER; }
            else                    { adjustment.wrap = Fs9_Gb9_WRAP; adjustment.divider = Fs9_Gb9_DIVIDER; }
        }
        else if(note[0] == 'A'){
                if(note[1] == '-') { adjustment.wrap = A_9_WRAP; adjustment.divider = A_8_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = As9_Bb9_WRAP; adjustment.divider = As9_Bb9_DIVIDER; }
            else                    { adjustment.wrap = Gs9_Ab9_WRAP; adjustment.divider = Gs9_Ab9_DIVIDER; }
        }
        else if(note[0] == 'B'){
            if(note[1] == '-')      { adjustment.wrap = B_9_WRAP; adjustment.divider = B_9_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Bs9_WRAP; adjustment.divider = Bs9_DIVIDER; }
            else                    { adjustment.wrap = As9_Bb9_WRAP; adjustment.divider = As9_Bb9_DIVIDER; }
        }

    }    


    else if(note[2] == '8')
    {
        if(note[0] == 'C'){
                if(note[1] == '-')  { adjustment.wrap = C_8_WRAP; adjustment.divider = C_8_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Cs8_Db8_WRAP; adjustment.divider = Cs8_Db8_DIVIDER; }
            else                    { adjustment.wrap = Cb8_WRAP; adjustment.divider = Cb8_DIVIDER; }
        }
        else if(note[0] == 'D'){
                 if(note[1] == '-') { adjustment.wrap = D_8_WRAP; adjustment.divider = D_8_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Ds8_Eb8_WRAP; adjustment.divider = Ds8_Eb8_DIVIDER; }
            else                    { adjustment.wrap = Cs8_Db8_WRAP; adjustment.divider = Cs8_Db8_DIVIDER; }
        }
        else if(note[0] == 'E') {
            if(note[1] == '-')      { adjustment.wrap = E_8_WRAP; adjustment.divider = E_8_DIVIDER;}
            else if(note[1] == '#') { adjustment.wrap = Es8_WRAP; adjustment.divider = Es8_DIVIDER; }
            else                    { adjustment.wrap = Ds8_Eb8_WRAP; adjustment.divider = Ds8_Eb8_DIVIDER; }
        }
        else if(note[0] == 'F'){
            if(note[1] == '-')      { adjustment.wrap = F_8_WRAP; adjustment.divider = F_8_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Fs8_Gb8_WRAP; adjustment.divider = Fs8_Gb8_DIVIDER; }
            else                    { adjustment.wrap = Fb8_WRAP; adjustment.divider = Fb8_DIVIDER; }
        }
        else if(note[0] == 'G'){
            if(note[1] == '-')      { adjustment.wrap = G_8_WRAP; adjustment.divider = G_8_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Gs8_Ab8_WRAP; adjustment.divider = Gs8_Ab8_DIVIDER; }
            else                    { adjustment.wrap = Fs8_Gb8_WRAP; adjustment.divider = Fs8_Gb8_DIVIDER; }
        }
        else if(note[0] == 'A'){
                if(note[1] == '-') { adjustment.wrap = A_8_WRAP; adjustment.divider = A_8_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = As8_Bb8_WRAP; adjustment.divider = As8_Bb8_DIVIDER; }
            else                    { adjustment.wrap = Gs8_Ab8_WRAP; adjustment.divider = Gs8_Ab8_DIVIDER; }
        }
        else if(note[0] == 'B'){
            if(note[1] == '-')      { adjustment.wrap = B_8_WRAP; adjustment.divider = B_8_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Bs8_WRAP; adjustment.divider = Bs8_DIVIDER; }
            else                    { adjustment.wrap = As8_Bb8_WRAP; adjustment.divider = As8_Bb8_DIVIDER; }
        }

    }    

    else if(note[2] == '7')
    {
        if(note[0] == 'C'){
                if(note[1] == '-')  { adjustment.wrap = C_7_WRAP; adjustment.divider = C_7_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Cs7_Db7_WRAP; adjustment.divider = Cs7_Db7_DIVIDER; }
            else                    { adjustment.wrap = Cb7_WRAP; adjustment.divider = Cb7_DIVIDER; }
        }
        else if(note[0] == 'D'){
                 if(note[1] == '-') { adjustment.wrap = D_7_WRAP; adjustment.divider = D_7_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Ds7_Eb7_WRAP; adjustment.divider = Ds7_Eb7_DIVIDER; }
            else                    { adjustment.wrap = Cs7_Db7_WRAP; adjustment.divider = Cs7_Db7_DIVIDER; }
        }
        else if(note[0] == 'E') {
            if(note[1] == '-')      { adjustment.wrap = E_7_WRAP; adjustment.divider = E_7_DIVIDER;}
            else if(note[1] == '#') { adjustment.wrap = Es7_WRAP; adjustment.divider = Es7_DIVIDER; }
            else                    { adjustment.wrap = Ds7_Eb7_WRAP; adjustment.divider = Ds7_Eb7_DIVIDER; }
        }
        else if(note[0] == 'F'){
            if(note[1] == '-')      { adjustment.wrap = F_7_WRAP; adjustment.divider = F_7_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Fs7_Gb7_WRAP; adjustment.divider = Fs7_Gb7_DIVIDER; }
            else                    { adjustment.wrap = Fb7_WRAP; adjustment.divider = Fb7_DIVIDER; }
        }
        else if(note[0] == 'G'){
            if(note[1] == '-')      { adjustment.wrap = G_7_WRAP; adjustment.divider = G_7_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Gs7_Ab7_WRAP; adjustment.divider = Gs7_Ab7_DIVIDER; }
            else                    { adjustment.wrap = Fs7_Gb7_WRAP; adjustment.divider = Fs7_Gb7_DIVIDER; }
        }
        else if(note[0] == 'A'){
                if(note[1] == '-') { adjustment.wrap = A_7_WRAP; adjustment.divider = A_7_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = As7_Bb7_WRAP; adjustment.divider = As7_Bb7_DIVIDER; }
            else                    { adjustment.wrap = Gs7_Ab7_WRAP; adjustment.divider = Gs7_Ab7_DIVIDER; }
        }
        else if(note[0] == 'B'){
            if(note[1] == '-')      { adjustment.wrap = B_7_WRAP; adjustment.divider = B_7_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Bs7_WRAP; adjustment.divider = Bs7_DIVIDER; }
            else                    { adjustment.wrap = As7_Bb7_WRAP; adjustment.divider = As7_Bb7_DIVIDER; }
        }

    }    


    else if(note[2] == '6')
    {
        if(note[0] == 'C'){
                if(note[1] == '-')  { adjustment.wrap = C_6_WRAP; adjustment.divider = C_6_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Cs6_Db6_WRAP; adjustment.divider = Cs6_Db6_DIVIDER; }
            else                    { adjustment.wrap = Cb6_WRAP; adjustment.divider = Cb6_DIVIDER; }
        }
        else if(note[0] == 'D'){
                 if(note[1] == '-') { adjustment.wrap = D_6_WRAP; adjustment.divider = D_6_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Ds6_Eb6_WRAP; adjustment.divider = Ds6_Eb6_DIVIDER; }
            else                    { adjustment.wrap = Cs6_Db6_WRAP; adjustment.divider = Cs6_Db6_DIVIDER; }
        }
        else if(note[0] == 'E') {
            if(note[1] == '-')      { adjustment.wrap = E_6_WRAP; adjustment.divider = E_6_DIVIDER;}
            else if(note[1] == '#') { adjustment.wrap = Es6_WRAP; adjustment.divider = Es6_DIVIDER; }
            else                    { adjustment.wrap = Ds6_Eb6_WRAP; adjustment.divider = Ds6_Eb6_DIVIDER; }
        }
        else if(note[0] == 'F'){
            if(note[1] == '-')      { adjustment.wrap = F_6_WRAP; adjustment.divider = F_6_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Fs6_Gb6_WRAP; adjustment.divider = Fs6_Gb6_DIVIDER; }
            else                    { adjustment.wrap = Fb6_WRAP; adjustment.divider = Fb6_DIVIDER; }
        }
        else if(note[0] == 'G'){
            if(note[1] == '-')      { adjustment.wrap = G_6_WRAP; adjustment.divider = G_6_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Gs6_Ab6_WRAP; adjustment.divider = Gs6_Ab6_DIVIDER; }
            else                    { adjustment.wrap = Fs6_Gb6_WRAP; adjustment.divider = Fs6_Gb6_DIVIDER; }
        }
        else if(note[0] == 'A'){
                if(note[1] == '-') { adjustment.wrap = A_6_WRAP; adjustment.divider = A_6_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = As6_Bb6_WRAP; adjustment.divider = As6_Bb6_DIVIDER; }
            else                    { adjustment.wrap = Gs6_Ab6_WRAP; adjustment.divider = Gs6_Ab6_DIVIDER; }
        }
        else if(note[0] == 'B'){
            if(note[1] == '-')      { adjustment.wrap = B_6_WRAP; adjustment.divider = B_6_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Bs6_WRAP; adjustment.divider = Bs6_DIVIDER; }
            else                    { adjustment.wrap = As6_Bb6_WRAP; adjustment.divider = As6_Bb6_DIVIDER; }
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

    else if(note[2] == '2')
    {
        if(note[0] == 'C'){
                if(note[1] == '-')  { adjustment.wrap = C_2_WRAP; adjustment.divider = C_2_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Cs2_Db2_WRAP; adjustment.divider = Cs2_Db2_DIVIDER; }
            else                    { adjustment.wrap = Cb2_WRAP; adjustment.divider = Cb2_DIVIDER; }
        }
        else if(note[0] == 'D'){
                 if(note[1] == '-') { adjustment.wrap = D_2_WRAP; adjustment.divider = D_2_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Ds2_Eb2_WRAP; adjustment.divider = Ds2_Eb2_DIVIDER; }
            else                    { adjustment.wrap = Cs2_Db2_WRAP; adjustment.divider = Cs2_Db2_DIVIDER; }
        }
        else if(note[0] == 'E') {
            if(note[1] == '-')      { adjustment.wrap = E_2_WRAP; adjustment.divider = E_2_DIVIDER;}
            else if(note[1] == '#') { adjustment.wrap = Es2_WRAP; adjustment.divider = Es2_DIVIDER; }
            else                    { adjustment.wrap = Ds2_Eb2_WRAP; adjustment.divider = Ds2_Eb2_DIVIDER; }
        }
        else if(note[0] == 'F'){
            if(note[1] == '-')      { adjustment.wrap = F_2_WRAP; adjustment.divider = F_2_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Fs2_Gb2_WRAP; adjustment.divider = Fs2_Gb2_DIVIDER; }
            else                    { adjustment.wrap = Fb2_WRAP; adjustment.divider = Fb2_DIVIDER; }
        }
        else if(note[0] == 'G'){
            if(note[1] == '-')      { adjustment.wrap = G_2_WRAP; adjustment.divider = G_2_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Gs2_Ab2_WRAP; adjustment.divider = Gs2_Ab2_DIVIDER; }
            else                    { adjustment.wrap = Fs2_Gb2_WRAP; adjustment.divider = Fs2_Gb2_DIVIDER; }
        }
        else if(note[0] == 'A'){
                if(note[1] == '-') { adjustment.wrap = A_2_WRAP; adjustment.divider = A_2_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = As2_Bb2_WRAP; adjustment.divider = As2_Bb2_DIVIDER; }
            else                    { adjustment.wrap = Gs2_Ab2_WRAP; adjustment.divider = Gs2_Ab2_DIVIDER; }
        }
        else if(note[0] == 'B'){
            if(note[1] == '-')      { adjustment.wrap = B_2_WRAP; adjustment.divider = B_2_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Bs2_WRAP; adjustment.divider = Bs2_DIVIDER; }
            else                    { adjustment.wrap = As2_Bb2_WRAP; adjustment.divider = As2_Bb2_DIVIDER; }
        }

    }  


    else if(note[2] == '1')
    {
        if(note[0] == 'C'){
                if(note[1] == '-')  { adjustment.wrap = C_1_WRAP; adjustment.divider = C_1_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Cs1_Db1_WRAP; adjustment.divider = Cs1_Db1_DIVIDER; }
            else                    { adjustment.wrap = Cb1_WRAP; adjustment.divider = Cb1_DIVIDER; }
        }
        else if(note[0] == 'D'){
                 if(note[1] == '-') { adjustment.wrap = D_1_WRAP; adjustment.divider = D_1_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Ds1_Eb1_WRAP; adjustment.divider = Ds1_Eb1_DIVIDER; }
            else                    { adjustment.wrap = Cs1_Db1_WRAP; adjustment.divider = Cs1_Db1_DIVIDER; }
        }
        else if(note[0] == 'E') {
            if(note[1] == '-')      { adjustment.wrap = E_1_WRAP; adjustment.divider = E_1_DIVIDER;}
            else if(note[1] == '#') { adjustment.wrap = Es1_WRAP; adjustment.divider = Es1_DIVIDER; }
            else                    { adjustment.wrap = Ds1_Eb1_WRAP; adjustment.divider = Ds1_Eb1_DIVIDER; }
        }
        else if(note[0] == 'F'){
            if(note[1] == '-')      { adjustment.wrap = F_1_WRAP; adjustment.divider = F_1_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Fs1_Gb1_WRAP; adjustment.divider = Fs1_Gb1_DIVIDER; }
            else                    { adjustment.wrap = Fb1_WRAP; adjustment.divider = Fb1_DIVIDER; }
        }
        else if(note[0] == 'G'){
            if(note[1] == '-')      { adjustment.wrap = G_1_WRAP; adjustment.divider = G_1_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Gs1_Ab1_WRAP; adjustment.divider = Gs1_Ab1_DIVIDER; }
            else                    { adjustment.wrap = Fs1_Gb1_WRAP; adjustment.divider = Fs1_Gb1_DIVIDER; }
        }
        else if(note[0] == 'A'){
                if(note[1] == '-') { adjustment.wrap = A_1_WRAP; adjustment.divider = A_1_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = As1_Bb1_WRAP; adjustment.divider = As1_Bb1_DIVIDER; }
            else                    { adjustment.wrap = Gs1_Ab1_WRAP; adjustment.divider = Gs1_Ab1_DIVIDER; }
        }
        else if(note[0] == 'B'){
            if(note[1] == '-')      { adjustment.wrap = B_1_WRAP; adjustment.divider = B_1_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Bs1_WRAP; adjustment.divider = Bs1_DIVIDER; }
            else                    { adjustment.wrap = As1_Bb1_WRAP; adjustment.divider = As1_Bb1_DIVIDER; }
        }

    }  

    else if(note[2] == '0')
    {
        if(note[0] == 'C'){
                if(note[1] == '-')  { adjustment.wrap = C_0_WRAP; adjustment.divider = C_0_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Cs0_Db0_WRAP; adjustment.divider = Cs0_Db0_DIVIDER; }
            else                    { adjustment.wrap = Cb0_WRAP; adjustment.divider = Cb0_DIVIDER; }
        }
        else if(note[0] == 'D'){
                 if(note[1] == '-') { adjustment.wrap = D_0_WRAP; adjustment.divider = D_0_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Ds0_Eb0_WRAP; adjustment.divider = Ds0_Eb0_DIVIDER; }
            else                    { adjustment.wrap = Cs0_Db0_WRAP; adjustment.divider = Cs0_Db0_DIVIDER; }
        }
        else if(note[0] == 'E') {
            if(note[1] == '-')      { adjustment.wrap = E_0_WRAP; adjustment.divider = E_0_DIVIDER;}
            else if(note[1] == '#') { adjustment.wrap = Es0_WRAP; adjustment.divider = Es0_DIVIDER; }
            else                    { adjustment.wrap = Ds0_Eb0_WRAP; adjustment.divider = Ds0_Eb0_DIVIDER; }
        }
        else if(note[0] == 'F'){
            if(note[1] == '-')      { adjustment.wrap = F_0_WRAP; adjustment.divider = F_0_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Fs0_Gb0_WRAP; adjustment.divider = Fs0_Gb0_DIVIDER; }
            else                    { adjustment.wrap = Fb0_WRAP; adjustment.divider = Fb0_DIVIDER; }
        }
        else if(note[0] == 'G'){
            if(note[1] == '-')      { adjustment.wrap = G_0_WRAP; adjustment.divider = G_0_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Gs0_Ab0_WRAP; adjustment.divider = Gs0_Ab0_DIVIDER; }
            else                    { adjustment.wrap = Fs0_Gb0_WRAP; adjustment.divider = Fs0_Gb0_DIVIDER; }
        }
        else if(note[0] == 'A'){
                if(note[1] == '-') { adjustment.wrap = A_0_WRAP; adjustment.divider = A_0_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = As0_Bb0_WRAP; adjustment.divider = As0_Bb0_DIVIDER; }
            else                    { adjustment.wrap = Gs0_Ab0_WRAP; adjustment.divider = Gs0_Ab0_DIVIDER; }
        }
        else if(note[0] == 'B'){
            if(note[1] == '-')      { adjustment.wrap = B_0_WRAP; adjustment.divider = B_0_DIVIDER; }
            else if(note[1] == '#') { adjustment.wrap = Bs0_WRAP; adjustment.divider = Bs0_DIVIDER; }
            else                    { adjustment.wrap = As0_Bb0_WRAP; adjustment.divider = As0_Bb0_DIVIDER; }
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


