#include <string.h>

#include "screens.h"
#include "../peripherals/I2C_Display/ssd1306.h"
#include "../sound/sound.h"

extern int screen;

extern float base_volume_level; 
extern float volume_level;
// extern float time_note_duration_ms = 1500;

void screen0(){

   // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    // zera o display inteiro
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    //Carregando primeira informação na tela:
    char *text[] = {
        " ",
        "",
        " ",
        "   SONG X BOX   ",
        "   ",
        " "};

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(ssd, 0, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);

    play_note(BUZZER_RIGHT_1, "C-4", base_volume_level*volume_level, 500 );
    sleep_ms(500);
    play_note(BUZZER_RIGHT_1, "D-4", base_volume_level*volume_level, 500 );
    sleep_ms(500);
    play_note(BUZZER_RIGHT_1, "E-4", base_volume_level*volume_level, 500 );
    sleep_ms(500);
    play_note(BUZZER_RIGHT_1, "F-4", base_volume_level*volume_level, 500 );
    sleep_ms(500);
    play_note(BUZZER_RIGHT_1, "G-4", base_volume_level*volume_level, 500 );
    sleep_ms(500);
    play_note(BUZZER_RIGHT_1, "A-4", base_volume_level*volume_level, 500 );
    sleep_ms(500);
    play_note(BUZZER_RIGHT_1, "B-4", base_volume_level*volume_level, 500 );
    sleep_ms(500);

    play_note(BUZZER_RIGHT_1, "C-4", base_volume_level*volume_level, 1000 );
    // play_note(BUZZER_LEFT_1,  "C-3", base_volume_level*volume_level, 1000 );
    sleep_ms(1000);

    // play_note(BUZZER_LEFT_1,  "C-3", base_volume_level*volume_level, 1000 );
    // sleep_ms(1000);

    
    //--: O rgb segura a tela aqui


    //mostra a tocar por x s
    // toca o som por x segundos 
    sleep_ms(500);

    screen = 1;

    return;
}