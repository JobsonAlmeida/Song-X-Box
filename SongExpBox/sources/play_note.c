#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "../headers/play_note.h"
#include "../types/Adjustment.h"
#include "../headers/get_divisor_wrap_from_note.h"



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