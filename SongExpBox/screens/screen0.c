#include <string.h>

#include "screens.h"
#include "../peripherals/I2C_Display/ssd1306.h"
#include "../sound/sound.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "../peripherals/MATRIZ_RGB/matriz_rgb.h"


extern int screen;

extern float base_volume_level; 
extern float volume_level;
// extern float time_note_duration_ms = 1500;


void show_sprite_on_led_matriz( int matriz[5][5][3], uint32_t duration ){

    // Desenhando Sprite contido na matriz.c
    for(int linha = 0; linha < 5; linha++){
        for(int coluna = 0; coluna < 5; coluna++){
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, matriz[coluna][linha][0], matriz[coluna][linha][1], matriz[coluna][linha][2]);
        }
    };

    npWrite();
    sleep_ms(duration);
    npClear();

    return;
}


void screen0(){

    // sprits da matriz de leds
    int matriz1[5][5][3] = {
        {{236, 23, 23}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {236, 23, 23}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{236, 23, 23}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {236, 23, 23}}
    };

    int matriz2[5][5][3] = {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {236, 23, 192}, {0, 0, 0}, {236, 23, 192}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {236, 23, 192}, {0, 0, 0}, {236, 23, 192}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    };

    int matriz3[5][5][3] = {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 170}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    };

    int matriz4[5][5][3] = {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {23, 199, 236}, {0, 0, 0}, {23, 199, 236}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {23, 199, 236}, {0, 0, 0}, {23, 199, 236}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    };

    int matriz5[5][5][3] = {
        {{23, 236, 29}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {23, 236, 29}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{23, 236, 29}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {23, 236, 29}}
    };

    int matriz6[5][5][3] =  {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {236, 192, 23}, {0, 0, 0}, {236, 192, 23}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {236, 192, 23}, {0, 0, 0}, {236, 192, 23}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    };

    int matriz7s[5][5][3] = {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {236, 136, 23}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    };

    int matriz7[5][5][3] =  {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {244, 99, 20}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    };

    int matriz8[5][5][3] = {
        {{236, 23, 51}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {236, 23, 51}},
        {{0, 0, 0}, {236, 23, 89}, {0, 0, 0}, {236, 23, 89}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {236, 23, 107}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {236, 23, 89}, {0, 0, 0}, {236, 23, 89}, {0, 0, 0}},
        {{236, 23, 51}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {236, 23, 51}}
    };

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


    //Introdução

    play_note(BUZZER_RIGHT_1, "C-4", base_volume_level*volume_level, 500 );
    for(int linha = 0; linha < 5; linha++){
        for(int coluna = 0; coluna < 5; coluna++){
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, matriz1[coluna][linha][0], matriz1[coluna][linha][1], matriz1[coluna][linha][2]);
        }
    };
    npWrite();    
    sleep_ms(500);
    

    play_note(BUZZER_RIGHT_1, "D-4", base_volume_level*volume_level, 500 );
    for(int linha = 0; linha < 5; linha++){
        for(int coluna = 0; coluna < 5; coluna++){
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, matriz2[coluna][linha][0], matriz2[coluna][linha][1], matriz2[coluna][linha][2]);
        }
    };
    npWrite();
    sleep_ms(500);

    play_note(BUZZER_RIGHT_1, "E-4", base_volume_level*volume_level, 500 );
    for(int linha = 0; linha < 5; linha++){
        for(int coluna = 0; coluna < 5; coluna++){
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, matriz3[coluna][linha][0], matriz3[coluna][linha][1], matriz3[coluna][linha][2]);
        }
    };
    npWrite();
    sleep_ms(500);

    play_note(BUZZER_RIGHT_1, "F-4", base_volume_level*volume_level, 500 );
    for(int linha = 0; linha < 5; linha++){
        for(int coluna = 0; coluna < 5; coluna++){
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, matriz4[coluna][linha][0], matriz4[coluna][linha][1], matriz4[coluna][linha][2]);
        }
    };
    npWrite();
    sleep_ms(500);

    play_note(BUZZER_RIGHT_1, "G-4", base_volume_level*volume_level, 500 );
    for(int linha = 0; linha < 5; linha++){
        for(int coluna = 0; coluna < 5; coluna++){
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, matriz5[coluna][linha][0], matriz5[coluna][linha][1], matriz5[coluna][linha][2]);
        }
    };
    npWrite();
    sleep_ms(500);

    play_note(BUZZER_RIGHT_1, "A-4", base_volume_level*volume_level, 500 );
    for(int linha = 0; linha < 5; linha++){
        for(int coluna = 0; coluna < 5; coluna++){
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, matriz6[coluna][linha][0], matriz6[coluna][linha][1], matriz6[coluna][linha][2]);
        }
    };
    npWrite();
    sleep_ms(500);

    play_note(BUZZER_RIGHT_1, "B-4", base_volume_level*volume_level, 500 );
    for(int linha = 0; linha < 5; linha++){
        for(int coluna = 0; coluna < 5; coluna++){
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, matriz7[coluna][linha][0], matriz7[coluna][linha][1], matriz7[coluna][linha][2]);
        }
    };
    npWrite();
    sleep_ms(500);

    play_note(BUZZER_RIGHT_1, "C-4", base_volume_level*volume_level, 1000 );
    for(int linha = 0; linha < 5; linha++){
        for(int coluna = 0; coluna < 5; coluna++){
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, matriz8[coluna][linha][0], matriz8[coluna][linha][1], matriz8[coluna][linha][2]);
        }
    };
    npWrite();
    sleep_ms(1000);


    npClear();
    npWrite();  
    sleep_ms(500);

    screen = 1;

    return;
}